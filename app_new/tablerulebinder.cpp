#include "tablerulebinder.h"

TableRuleBinder::TableRuleBinder( RuleChecker* ruleChecker, QAbstractTableModel* aTable, QWidget *parent): 
AbstractRuleBinder(ruleChecker, parent), model(aTable){

    connect(this, SIGNAL(recordAdded(const QString)), this,
    SLOT(onFirePostTrigger(const QString)));
}

TableRuleBinder::~TableRuleBinder()
{

}

void TableRuleBinder::connectSignals()
{
    connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this,
    SLOT(onFireTriggerIndex(const QModelIndex&)));
}

void TableRuleBinder::onFireTriggerIndex(const QModelIndex& tl)
{
    setCurRow(tl.row());
    if (!getPreTriggerGeneric(model->data(tl),tl.column()) ) emit showError(tr("Could not activate pre-trigger!"));
}

bool TableRuleBinder::getTableName(QString& strTableName)
{
    if ( qobject_cast<QSqlRelationalTableModel*>(model)==0) return false;
    QSqlRelationalTableModel* relModel=qobject_cast<QSqlRelationalTableModel*>(model);
    // Remove extra quotes!!!
    strTableName=FixTableName(relModel->tableName());
    return (strTableName.size()>0);
}

bool TableRuleBinder::getPreTrigger(const QString strRule, const QVariant& newValue, const size_t field)
{
    QModelIndex index=model->index(getCurRow(),field);
    if (index.isValid()){
        // Looks for parameters to bind!
        if (strRule.indexOf(tr(":par"))!=-1){
            if (!applyRule(strRule,index,RuleChecker::PRETRIGGER,newValue)) return false;
        }
        else{
            if (!applyRule(strRule,index,RuleChecker::PRETRIGGER)) return false;
        }
    }

    return true;
}

QVariant TableRuleBinder::getVal(const size_t field)
{
    QModelIndex index=model->index(getCurRow(),field);
    return model->data(index,Qt::DisplayRole);
}

bool TableRuleBinder::applyRule(QString strRule, const QModelIndex& tl, const RuleChecker::Type eType, const QVariant varPar)
{
    if (!parseRuleReferences(strRule)) return false;

    QSqlQuery query;
    if (!ruleCheckerPtr->applyRule(strRule,query,varPar)) return false;
    query.first();
    QVariant val=query.value(0);

    switch ( eType ) {

      case RuleChecker::DEFAULT://Does not apply for tables
      case RuleChecker::PRETRIGGER:

          if (val.toString().compare(strNothing)!=0){
              model->setData(tl,query.value(0),Qt::DisplayRole);// First set the display value 
              if (!model->setData(tl,query.value(1),Qt::EditRole)) return false;// Then set the actual value in the model
          }
          break;

      case RuleChecker::VALIDATION:
          //TODO: implement validation?

            break;

      default : 
        // It should never come here!
        return false;
}

    return true;
}