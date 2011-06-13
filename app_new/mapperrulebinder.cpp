#include "mapperrulebinder.h"
#include "customtimectrl.h"

MapperRuleBinder::MapperRuleBinder( RuleChecker* ruleChecker, QList<QDataWidgetMapper*> aLMapper, const QString strForm, QWidget *parent): 
AbstractRuleBinder(ruleChecker, strForm, parent), lMapper(aLMapper){

    //connect(this, SIGNAL(recordAdded(const size_t)), this,
    //SLOT(onFirePostTrigger(const size_t)));
}

MapperRuleBinder::~MapperRuleBinder()
{

}

void MapperRuleBinder::connectSignals()
{
    for (size_t j=0; j < lMapper.count(); ++j){

        for (size_t i=0; i < (size_t)lMapper[j]->model()->columnCount(); ++i){

            QWidget* aWidget=lMapper[j]->mappedWidgetAt(i);
            if (aWidget!=0){

                if ( qobject_cast<QLineEdit*>(aWidget)!=0 ){
                    QLineEdit* lineEdit=qobject_cast<QLineEdit*>(aWidget);

                    connect(lineEdit, SIGNAL(editingFinished()), this,
                        SLOT(onFireTrigger()));

                }
                else if ( qobject_cast<CustomTimeCtrl*>(aWidget)!=0 ){
                    CustomTimeCtrl* customTime=qobject_cast<CustomTimeCtrl*>(aWidget);

                    connect(customTime, SIGNAL(dateTimeChanged ( const QDateTime &)), this,
                        SLOT(onFireTrigger()));
                }
                else if ( qobject_cast<QComboBox*>(aWidget)!=0){

                    QComboBox* comboBox=qobject_cast<QComboBox*>(aWidget);

                    connect(comboBox, SIGNAL(currentIndexChanged(const QString&)), this,
                        SLOT(onFireTriggerText(const QString&)));

                }
                else if ( qobject_cast<ButtonGroup*>(aWidget)!=0 ){
                    ButtonGroup* buttonGroup=qobject_cast<ButtonGroup*>(aWidget);

                    connect(buttonGroup, SIGNAL(buttonClicked(int)), this,
                        SLOT(onFireTrigger()));
                }
                else if ( qobject_cast<QSpinBox*>(aWidget)!=0){

                    QSpinBox* spinBox=qobject_cast<QSpinBox*>(aWidget);

                    connect(spinBox, SIGNAL(valueChanged(const QString&)), this,
                        SLOT(onFireTriggerText(const QString&)));//SHOULD WE PASS AN INTEGER INSTEAD?

                }
            }
        }
    }
}

void MapperRuleBinder::onFireTrigger()
{
    if ( qobject_cast<QLineEdit*>(sender())!=0 ){
        QLineEdit *senderWidget = (QLineEdit *)sender();
        onFireTriggerGeneric(senderWidget,senderWidget->text());
    }
    else if ( qobject_cast<CustomTimeCtrl*>(sender())!=0 ){
        CustomTimeCtrl *senderWidget = (CustomTimeCtrl *)sender();
        onFireTriggerGeneric(senderWidget,senderWidget->dateTime());
    }
    else if ( qobject_cast<ButtonGroup*>(sender())!=0 ){
        ButtonGroup *senderWidget = (ButtonGroup *)sender();
        onFireTriggerGeneric(senderWidget,senderWidget->getCheckedId());
    }
}

void MapperRuleBinder::onFireTriggerText(const QString& strNewText)
{
    if ( qobject_cast<QWidget*>(sender())==0 ) return;
    QWidget *senderWidget = (QWidget *)sender();

    onFireTriggerGeneric(senderWidget, strNewText);
}

void MapperRuleBinder::onFireTriggerGeneric(QWidget* senderWidget, const QVariant& newValue)
{
    for (size_t j=0; j < lMapper.count(); ++j){

        // Find widgets mapped to sections of the model.
        for (size_t i=0; i < (size_t)lMapper[j]->model()->columnCount(); ++i){

            QWidget* aWidget=lMapper[j]->mappedWidgetAt(i);
            if (aWidget!=0){
                if (aWidget==senderWidget){
                    // Get Pre-trigger.
                    QString strTable;
                    if (getTableName(lMapper[j],strTable)){
                        if (!getPreTriggerGeneric(newValue,i,j)) emit showError(tr("Could not activate pre-trigger rule!"),false);
                        // Get Validation.
                        if (!getValidation(newValue,j,i)) emit showError(tr("Could not activate validation rule!"),false);
                    } else emit showError(tr("Could not retrieve the table name for this mapper!"),false);
                }
            }

        }
    }
}

bool MapperRuleBinder::getTableName(const QDataWidgetMapper* mapper, QString& strTableName) const
{
    if ( qobject_cast<QSqlTableModel*>(mapper->model())==0) return false;

    QSqlTableModel* tModel=qobject_cast<QSqlTableModel*>(mapper->model());
    // Remove extra quotes!!!
    strTableName=FixTableName(tModel->tableName());
    //strTableName=tModel->tableName().remove(tr("\""));
    return (strTableName.size()>0);
}

QDataWidgetMapper* MapperRuleBinder::getMapperFromTable(const QString strTableName)
{
    for (size_t j=0; j < lMapper.count(); ++j){

          QSqlTableModel* tModel=qobject_cast<QSqlTableModel*>
              (lMapper[j]->model());
          if (tModel!=0){
              QString strModelTableName=FixTableName(tModel->tableName());
              if (strModelTableName.compare(strTableName)==0)
                  return lMapper[j];
          }
    }
    return 0;
}

bool MapperRuleBinder::getPreTrigger(const QString strRule, const QVariant& newValue, const size_t field, const size_t mapper)
{
    QWidget* aWidget=lMapper.at(mapper)->mappedWidgetAt(field);
    if (aWidget!=0){
        // Looks for parameters to bind!
        if (strRule.indexOf(tr(":par"))!=-1){
            if (!applyRule(strRule,aWidget,RuleChecker::PRETRIGGER,newValue)) return false;
        }
        else{
            if (!applyRule(strRule,aWidget,RuleChecker::PRETRIGGER)) return false;
        }
    }

    return true;
}

bool MapperRuleBinder::getCurrentWidgetValue(QWidget* aWidget, QVariant& val)
{
    if ( qobject_cast<QLineEdit*>(aWidget)!=0 )
        val=qobject_cast<QLineEdit*>(aWidget)->text();
    else if ( qobject_cast<QDateEdit*>(aWidget)!=0 )
        val=qobject_cast<QDateEdit*>(aWidget)->date();
/*    else if ( qobject_cast<TimeStampDateEdit*>(aWidget)!=0 ){
        val=qobject_cast<TimeStampDateEdit*>(aWidget)->date();
    }*/
    else if ( qobject_cast<QComboBox*>(aWidget)!=0 )
        val=qobject_cast<QComboBox*>(aWidget)->currentText();
    else if ( qobject_cast<ButtonGroup*>(aWidget)!=0 )
        val=qobject_cast<ButtonGroup*>(aWidget)->getCheckedId();//TODO: TEST THIS!
    else if ( qobject_cast<QSpinBox*>(aWidget)!=0 )
        val=qobject_cast<QSpinBox*>(aWidget)->value();
    else return false;

    return true;
}

bool MapperRuleBinder::fetchRules(const MapRules& map, const RuleChecker::Type eType, size_t mapper,
                                   QVariant varPar, int field)
{
    //Must pass field (to validate) to validation rules!
    if (eType==RuleChecker::VALIDATION && field==-1) return false;

        MapReferences::const_iterator it = ruleCheckerPtr->mapReferences.constBegin();
        while (it != ruleCheckerPtr->mapReferences.constEnd()) {
            if ( (it.value()->m_strForm.compare(m_strForm)==0) &&
                (field==-1 || (it.value()->m_idxField==field && it.value()->m_idxMapper==mapper)) ){
                // Found a reference: see if there is a widget mapped to this!

                QWidget* aWidget=lMapper.at(mapper)->mappedWidgetAt(it.value()->m_idxField);
                if ( aWidget!=0 ) {
                        // Found a widget mapped to this field: let's have a look at the values!
                        MapRules::const_iterator itt = map.find(it.key());
                        while (itt != map.constEnd() && itt.key()==it.key()) {
                            if (eType==RuleChecker::PRESUBMIT){
                                if (!getCurrentWidgetValue(aWidget,varPar)) return false;
                            }
                            if (!applyRule(itt.value(),aWidget,eType,varPar)) return false;
                            ++itt;
                        }
                }
            }
            ++it;
        }

    return true;
}

bool MapperRuleBinder::enableWidget(QWidget* aWidget, const QVariant val)
{
    if (val.toString().compare(strEnable, Qt::CaseInsensitive)==0)
        aWidget->setEnabled(true);
    else if (val.toString().compare(strDisable, Qt::CaseInsensitive)==0)
        aWidget->setEnabled(false);
    else return false;

    return true;
}

QVariant MapperRuleBinder::getVal(const size_t field, const size_t mapper)
{
    QVariant val;/*
    QDataWidgetMapper* mapper=getMapperFromTable(strTable);
    if (mapper==0) return QVariant();
*/
    if (!getCurrentWidgetValue
        (lMapper.at(mapper)->mappedWidgetAt(field),val)) return false;
    return val;
}

bool MapperRuleBinder::applyRule(QString strRule, QWidget* aWidget, const RuleChecker::Type eType,
                                 const QVariant varPar)
{
    QString originalRule=strRule;//store the original value, so that we can query it later!

    if (!parseRuleReferences(strRule)) return false;

    QSqlQuery query;
    if (!ruleCheckerPtr->applyRule(strRule,query,varPar)) return false;
    query.first();
    QVariant val=query.value(0);

    switch ( eType ) {

      case RuleChecker::DEFAULT:
      case RuleChecker::PRETRIGGER:

          //Reserved Words to Trigger Enable/Disable of the widget: ENABLE, DISABLE
          if (val.toString().compare(strEnable, Qt::CaseInsensitive)==0 ||
              val.toString().compare(strDisable, Qt::CaseInsensitive)==0)
          {
              if (!enableWidget(aWidget,val)) return false;
          }else{

            // Cast control to the right type (Permissibyle types: QlineEdit, QDateEdit, QComboBox, ButtonGroup)
            if ( qobject_cast<QLineEdit*>(aWidget)!=0 )
                qobject_cast<QLineEdit*>(aWidget)->setText(val.toString());
            else if ( qobject_cast<QDateEdit*>(aWidget)!=0 )
                qobject_cast<QDateEdit*>(aWidget)->setDate(val.toDate());
            else if ( qobject_cast<CustomTimeCtrl*>(aWidget)!=0 ){
                QDateTime myDate;
                if (val.type()==QVariant::Date || val.type()==QVariant::DateTime){
                    QDateTime dt(val.toDateTime());
                    myDate=dt;
                }/*
                else if (val.type()==QVariant::String){
                    QString strDate=val.toString();
                    myDate=QDateTime::fromString(strDate,defaultFormat);
                }*/
                qobject_cast<CustomTimeCtrl*>(aWidget)->setDateTime(myDate);
            }
            else if ( qobject_cast<QComboBox*>(aWidget)!=0 )
                qobject_cast<QComboBox*>(aWidget)->setCurrentIndex(
                    qobject_cast<QComboBox*>(aWidget)->findText(val.toString()));
            else if ( qobject_cast<ButtonGroup*>(aWidget)!=0 )
                qobject_cast<ButtonGroup*>(aWidget)->checkId(val.toBool());
            else if ( qobject_cast<QSpinBox*>(aWidget)!=0 )
                qobject_cast<QSpinBox*>(aWidget)->setValue(val.toInt());
            else return false;
          }
          break;

      case RuleChecker::VALIDATION:
      case RuleChecker::PRESUBMIT:

          if (val.toBool()==0){
                // Look for error
                QSqlQuery eQuery;
                eQuery.prepare(tr("SELECT description, [rule] FROM dbo.UI_Rules WHERE ([rule] LIKE :rule)"));
                eQuery.bindValue(tr(":rule"),originalRule);
                eQuery.setForwardOnly(true);
                if (!eQuery.exec()) return false;
                eQuery.first();
                //QString strError=tr("This value is not allowed: ").append(eQuery.value(0).toString());
                QString strError=eQuery.value(0).toString();
                emit showError(strError);
                aWidget->setFocus();
                if ( qobject_cast<QLineEdit*>(aWidget)!=0 )
                    qobject_cast<QLineEdit*>(aWidget)->selectAll();/*
                else if ( qobject_cast<TimeStampDateEdit*>(aWidget)!=0 ){
                    qobject_cast<TimeStampDateEdit*>(aWidget)->selectAll();
                    qobject_cast<TimeStampDateEdit*>(aWidget)->setFocus();
                }*/
                else if ( qobject_cast<QComboBox*>(aWidget)!=0 ){
                    qobject_cast<QComboBox*>(aWidget)->setFocus();
                    if (qobject_cast<QComboBox*>(aWidget)->isEditable())
                        qobject_cast<QComboBox*>(aWidget)->lineEdit()->selectAll();
                }
                else if ( qobject_cast<QSpinBox*>(aWidget)!=0 ){
                    qobject_cast<QSpinBox*>(aWidget)->setFocus();
                    qobject_cast<QSpinBox*>(aWidget)->selectAll();
                }
                // Note: do we want to validate a RadioButton?
                else return false;

                return false;

            }else{
            emit showStatus(tr("Value successfully validated!"));
            }

            break;

      default : 
        // It should never come here!
        return false;
}

    return true;
}
