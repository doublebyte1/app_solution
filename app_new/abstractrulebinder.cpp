#include "abstractrulebinder.h"

AbstractRuleBinder::AbstractRuleBinder( RuleChecker* ruleChecker, const QString strForm, QWidget *parent): 
QObject(parent), ruleCheckerPtr(ruleChecker), m_strForm(strForm){

    // Let's not connect directly to Rulechecker, so establish all signal-slot dialog here!
        connect(this, SIGNAL(addRecord(const size_t)), this,
        SLOT(getDefaultValues(const size_t)));

        connect(this, SIGNAL(submitRecord(const size_t)), this,
        SLOT(getPreSubmitValidation(const size_t)));
}

void AbstractRuleBinder::init()
{
    connectSignals();//! Connect the signal for pre trigger rules, *polymorphically* according with the type of widget!
}

bool AbstractRuleBinder::parseRuleReferences(QString& strRule)
{
    QList<size_t> idList;
    QMultiMap<QString, QMap<size_t,size_t> > mapLookups;
    if (!ruleCheckerPtr->parseRule(strRule,idList,mapLookups)) return false;
    if (mapLookups.size()>0){

        size_t ctr=0;
        //QString strTable;
        //if (!getTableName(strTable)) return false;
        QMultiMap<QString,  QMap<size_t,size_t> >::iterator j = mapLookups.find(m_strForm);
         while (j != mapLookups.end() && j.key() == m_strForm) {

             QString strResult;

             size_t field=j.value().begin().value();
             size_t mapper=j.value().begin().key();

             QVariant var=getVal(field,mapper);
             if (var.type()==QVariant::Invalid) return false;
             if (var.type()==QVariant::String) strResult=tr("'") + var.toString() + tr("'");
             else strResult=var.toString();

             QString searchStr=StrRulePtr + tr("(") + QVariant(idList.at(ctr)).toString() + tr(")");
             strRule=strRule.replace(searchStr,
                 strResult);
             ctr++;

             ++j;
         }

    }
    return true;
}
/*
void AbstractRuleBinder::onFirePostTrigger(const QString strTable, const QVariant varPar)
{
    bool bOk=true;

    QString strFixTable=FixTableName(strTable);
    MapRules::const_iterator it = ruleCheckerPtr->mapPostTriggerRls.constBegin();
    while (it != ruleCheckerPtr->mapPostTriggerRls.constEnd()) {

        // Retrieve rules on the reference table
        MapReferences::const_iterator itt = ruleCheckerPtr->mapReferences.find(it.key());
        while (itt != ruleCheckerPtr->mapReferences.constEnd() && itt.key()==it.key()) {
            if ( itt.value()->m_strTable.compare(strFixTable)==0){
            // Found a post-trigger rule for this table: let's run it!
                QSqlQuery query;
                if (!ruleCheckerPtr->applyRule(it.value(),query,varPar)){
                    bOk=false;
                    emit showError(tr("Could not run Post-Trigger Query!"));
                }
            }
            ++itt;
        }
        ++it;
    }
    emit finishedPostTrigger(bOk);
}
*/
bool AbstractRuleBinder::getDefaultValues(const size_t mapper)
{
    return fetchRules(ruleCheckerPtr->mapDefaultRls,RuleChecker::DEFAULT,mapper);
}

void AbstractRuleBinder::getPreSubmitValidation(const size_t mapper)
{
    bool bOk=fetchRules(ruleCheckerPtr->mapPreSubmitRls,RuleChecker::PRESUBMIT,mapper);
    emit finishedPreSubmit(bOk);
}

bool AbstractRuleBinder::getValidation(const QVariant& newValue, const size_t mapper, const size_t field)
{
    return fetchRules(ruleCheckerPtr->mapValidationRls, RuleChecker::VALIDATION, mapper, newValue, field);
}

bool AbstractRuleBinder::getPreTriggerGeneric(const QVariant& newValue, const size_t field, const size_t mapper)
{
        // First find the key
        MapReferences::const_iterator it = ruleCheckerPtr->mapReferences.constBegin();
        while (it != ruleCheckerPtr->mapReferences.constEnd()) {
            if ( it.value()->oCellPtr && it.value()->oCellPtr->m_strForm.compare(m_strForm)==0){
                if (it.value()->oCellPtr->m_idxField==field){
                    // Found a reference, let's fetch the data at the other hash!
                    MapRules::const_iterator itt = ruleCheckerPtr->mapPreTriggers.find(it.key());
                    while (itt != ruleCheckerPtr->mapPreTriggers.constEnd() && itt.key()==it.key()) {
                        // Grabb the pointed widget, to update
                        if (!getPreTrigger(itt.value(),newValue, it.value()->m_idxField,mapper)) return false;
                        ++itt;
                    }
                }
            }
            ++it;


    }
    return true;
}
////////////////////////////////////////////////////
static const char *strSlash = QT_TRANSLATE_NOOP("slash", "\"");

QString FixTableName(QString tableName)
{
    QString str=tableName.remove(strSlash);
    return str;
}