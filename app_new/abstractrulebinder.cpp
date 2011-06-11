#include "abstractrulebinder.h"

AbstractRuleBinder::AbstractRuleBinder( RuleChecker* ruleChecker, QWidget *parent): 
QObject(parent), ruleCheckerPtr(ruleChecker){

    // Let's not connect directly to Rulechecker, so establish all signal-slot dialog here!
        connect(this, SIGNAL(addRecord()), this,
        SLOT(getDefaultValues()));

        connect(this, SIGNAL(submitRecord()), this,
        SLOT(getPreSubmitValidation()));
}

void AbstractRuleBinder::init()
{
    connectSignals();//! Connect the signal for pre trigger rules, *polymorphically* according with the type of widget!
}

bool AbstractRuleBinder::parseRuleReferences(QString& strRule)
{
    QList<size_t> idList;
    QMultiMap<QString, size_t> mapLookups;
    if (!ruleCheckerPtr->parseRule(strRule,idList,mapLookups)) return false;
    if (mapLookups.size()>0){

        size_t ctr=0;
        QString strTable;
        if (!getTableName(strTable)) return false;
        //For now we only support references to the same binder/table!
        QMultiMap<QString, size_t>::iterator j = mapLookups.find(strTable);
         while (j != mapLookups.end() && j.key() == strTable) {

             QString strResult;
             QVariant var=getVal(j.value());
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

bool AbstractRuleBinder::getDefaultValues()
{
    return fetchRules(ruleCheckerPtr->mapDefaultRls,RuleChecker::DEFAULT);
}

void AbstractRuleBinder::getPreSubmitValidation()
{
    bool bOk=fetchRules(ruleCheckerPtr->mapPreSubmitRls,RuleChecker::PRESUBMIT);
    emit finishedPreSubmit(bOk);
}

bool AbstractRuleBinder::getValidation(const QVariant& newValue, const size_t field)
{
    return fetchRules(ruleCheckerPtr->mapValidationRls, RuleChecker::VALIDATION, newValue, field);
}

bool AbstractRuleBinder::getPreTriggerGeneric(const QVariant& newValue, const size_t field)
{
        // Retrieve table name
        QString strTable;
        if (!getTableName(strTable)) return false;

        // First find the key
        MapReferences::const_iterator it = ruleCheckerPtr->mapReferences.constBegin();
        while (it != ruleCheckerPtr->mapReferences.constEnd()) {
            if ( it.value()->oCellPtr && it.value()->oCellPtr->m_strTable.compare(strTable)==0){
                if (it.value()->oCellPtr->m_idxField==field){
                    // Found a reference, let's fetch the data at the other hash!
                    MapRules::const_iterator itt = ruleCheckerPtr->mapPreTriggers.find(it.key());
                    while (itt != ruleCheckerPtr->mapPreTriggers.constEnd() && itt.key()==it.key()) {
                        // Grabb the pointed widget, to update
                        if (it.value()->m_strTable!=strTable) return false;
                        if (!getPreTrigger(itt.value(),newValue, it.value()->m_idxField)) return false;
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