#include "abstractrulebinder.h"
#include "generictab.h"

AbstractRuleBinder::AbstractRuleBinder( RuleChecker* ruleChecker, Sample* sample, const QString strForm, QWidget *parent): 
QObject(parent), ruleCheckerPtr(ruleChecker), m_strForm(strForm), m_sample(sample){

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

bool AbstractRuleBinder::parseSample(const QString strRule, QMap<QString,QString>& mapLookups)
{
    int left=0,right=0;
    while (left!=-1){
        left=strRule.indexOf(QString(StrRuleSample+ tr("(")),left,Qt::CaseInsensitive);
        if (left==-1) break;
        right=strRule.indexOf(tr(")"),left);
        if (right==0) break;
        //parse keyword ///////////////
        int start=left+ QString(StrRuleSample+ tr("(")).length();
        int len=right-start;
        QString keyword=strRule.mid(start,len);
        if (m_sample==0) return false;// check, just in case...
        if (keyword.compare(tr("frameId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->frameId).toString());
        else if (keyword.compare(tr("frameTimeId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->frameTimeId).toString());
        else if (keyword.compare(tr("minorStrataId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->minorStrataId).toString());
        else if (keyword.compare(tr("cellId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->cellId).toString());
        else if (keyword.compare(tr("vesselTypeId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->vesselTypeId).toString());
        else if (keyword.compare(tr("sampVesselId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->sampVesselId).toString());
        else if (keyword.compare(tr("tripId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->tripId).toString());
        else if (keyword.compare(tr("operationId"))==0)
            mapLookups.insert(keyword,QVariant(m_sample->operationId).toString());
        else if (keyword.compare(tr("bLogBook"))==0)//cast the bool to int, b4 converting into string!
            mapLookups.insert(keyword,QVariant(QVariant(m_sample->bLogBook).toInt()).toString());
        else return false;

        left=start+len;//found next occurrence
    }

    return true;
}

bool AbstractRuleBinder::parseRuleReferences(QString& strRule)
{
    QMultiMap<size_t, QMap<size_t,size_t> > mapLookups;
    if (!ruleCheckerPtr->parseRule(strRule,mapLookups)) return false;
    if (mapLookups.size()>0){

        QMultiMap<size_t,  QMap<size_t,size_t> >::iterator j = mapLookups.begin();
         while (j != mapLookups.end()) {

             QString strResult;

             size_t field=j.value().begin().value();
             size_t mapper=j.value().begin().key();

             QVariant var=getVal(field,mapper);
             if (var.type()==QVariant::Invalid) return false;
             if (var.type()==QVariant::String) strResult=tr("'") + var.toString() + tr("'");
             else strResult=var.toString();

             QString searchStr=StrRulePtr + tr("(") + QVariant(j.key()).toString() + tr(")");
             strRule=strRule.replace(searchStr,
                 strResult);

             ++j;
         }

    }

    //search for references to the current sample
    QMap<QString, QString> mapSample;
    if (!parseSample(strRule,mapSample)) return false;

    QMap<QString, QString>::iterator j = mapSample.begin();
     while (j != mapSample.end()) {

             QString searchStr=StrRuleSample + tr("(") + QVariant(j.key()).toString() + tr(")");
             strRule=strRule.replace(searchStr,
                 j.value());

             //qDebug() << strRule << endl;

         ++j;
     }

    return true;
}

bool AbstractRuleBinder::getDefaultValues()
{
    bool bOk=fetchRules(ruleCheckerPtr->mapDefaultRls,RuleChecker::DEFAULT);
    emit defaultValuesRead();
    return bOk;
}

void AbstractRuleBinder::getPreSubmitValidation()
{
    bool bOk=fetchRules(ruleCheckerPtr->mapPreSubmitRls,RuleChecker::PRESUBMIT);
    emit finishedPreSubmit(bOk);
}

bool AbstractRuleBinder::getValidation(const QVariant& newValue, const size_t mapper, const size_t field)
{
    return fetchRules(ruleCheckerPtr->mapValidationRls, RuleChecker::VALIDATION, mapper, field, newValue);
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
                        if (!getPreTrigger(itt,newValue, it.value()->m_idxField,mapper)) return false;
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