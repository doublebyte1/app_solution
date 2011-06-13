#include "rulechecker.h"
#include "buttongroup.h"
//#include "timestampdateedit.h"
#include "sql.h"

RuleChecker::RuleChecker(QWidget* parent)
    : QWidget(parent)
{
}

RuleChecker::~RuleChecker()
{
// No pointers to release, since boost takes care of everything!
}

bool RuleChecker::init()
{
    return ( buildHashes() );
}

const bool RuleChecker::GetTypeFromString(const QString strType, Type& type)
{
    if (strType.compare(tr("default"),Qt::CaseInsensitive)==0)
    {
        type=RuleChecker::DEFAULT;
    }else if (strType.compare(tr("pre-trigger"),Qt::CaseInsensitive)==0)
    {
        type=RuleChecker::PRETRIGGER;
    }else if (strType.compare(tr("validation"),Qt::CaseInsensitive)==0)
    {
        type=RuleChecker::VALIDATION;
    }else if (strType.compare(tr("post-trigger"),Qt::CaseInsensitive)==0)
    {
        type=RuleChecker::POSTTRIGGER;
    }else if (strType.compare(tr("pre-submit"),Qt::CaseInsensitive)==0)
    {
        type=RuleChecker::PRESUBMIT;
    } else return false;

    return true;
}

MapRules* RuleChecker::GetContainerFromType(const Type& type)
{
      switch ( type )
      {
      case RuleChecker::DEFAULT:
            return &mapDefaultRls;
      case RuleChecker::PRETRIGGER:
            return &mapPreTriggers;
      case RuleChecker::POSTTRIGGER:
            return &mapPostTriggerRls;
      case RuleChecker::VALIDATION:
            return &mapValidationRls;
      case RuleChecker::PRESUBMIT:
            return &mapPreSubmitRls;
       default:
             return 0;
      }
}

bool RuleChecker::buildHashes()
{
    //First run queries
    QString sqlActiveRules=tr("SELECT distinct dbo.UI_Rules.id_rules, dbo.UI_Rules.field, dbo.UI_Rules.mapper, "
        "dbo.UI_Forms.Name as form_name, "
        "dbo.UI_Rules.[rule], dbo.UI_Rule_Types.name AS type_name, dbo.UI_Rules.[table] "
        "FROM dbo.UI_Rule_Ptrs RIGHT OUTER JOIN dbo.UI_Rules ON dbo.UI_Rule_Ptrs.id_rules = "
        "dbo.UI_Rules.id_rules INNER JOIN dbo.UI_Rule_Types ON dbo.UI_Rules.type = dbo.UI_Rule_Types.id_rule_types "
        "INNER JOIN UI_Forms ON UI_Rules.form=UI_Forms.ID "
        "WHERE (dbo.UI_Rules.active=1)");

    QSqlQuery query;
    if (!query.prepare(sqlActiveRules)) return false;
    QSqlQuery triggerPtrQuery;
    if (!triggerPtrQuery.prepare(
        tr("SELECT dbo.UI_Rule_Ptrs.[table], dbo.UI_Rule_Ptrs.field, dbo.UI_Rule_Ptrs.id_rules, "
        "dbo.UI_Rule_Ptrs.mapper, dbo.UI_Forms.Name as form_name"
        "dbo.UI_Rule_Ptrs.ID FROM dbo.UI_Rule_Ptrs INNER JOIN dbo.UI_Rules ON "
        "dbo.UI_Rule_Ptrs.id_rules = dbo.UI_Rules.id_rules "
        "INNER JOIN UI_Forms ON UI_Rule_Ptrs.form=UI_Forms.ID "
        "WHERE (dbo.UI_Rule_Ptrs.id_rules = :id AND dbo.UI_Rules.active=1)"
        )) ){
            return false;
        }

    size_t naId;//Id for n/a rule
    if (!getNaRuleID(naId)) return false;

    query.setForwardOnly(true);
    if (!query.exec()) return false;
    if (query.numRowsAffected()>0){//Maybe we don't have any active rules?

        while (query.next()){
            QString table=query.value(query.record().indexOf(tr("table"))).toString();
            size_t field=query.value(query.record().indexOf(tr("field"))).toInt();
            QString rule=query.value(query.record().indexOf(tr("rule"))).toString();
            QString form=query.value(query.record().indexOf(tr("form_name"))).toString();
            size_t mapper=query.value(query.record().indexOf(tr("mapper"))).toInt();
            size_t id=(size_t)query.value(query.record().indexOf(tr("id_rules"))).toInt();
            RuleChecker::Type eRuleType;
            if (!GetTypeFromString(query.value(query.record().indexOf(tr("type_name"))).toString(),eRuleType)) return false;

            if (eRuleType==RuleChecker::DEFAULT || eRuleType==RuleChecker::PRESUBMIT
                || eRuleType==RuleChecker::VALIDATION || eRuleType==RuleChecker::POSTTRIGGER){
                // Watch out this piece of code, cause the pointers and references can get us into a lot of trouble!
                MapRules* mapPtr=GetContainerFromType(eRuleType);
                    if (mapPtr!=0)
                        if (!standardRuleInsertion(rule,id,cellShrPtr(new cell(table,field,form,mapper)),*mapPtr)) return false;
            }else if (eRuleType==RuleChecker::PRETRIGGER){
                // Retrieve the settings from the origin column
                size_t id=query.value(query.record().indexOf(tr("id_rules"))).toInt();
                triggerPtrQuery.bindValue(tr(":id"), id);
                triggerPtrQuery.setForwardOnly(true);
                if (!triggerPtrQuery.exec()|| triggerPtrQuery.numRowsAffected()<1){
                    return false;
                }
                // Watch out because we can have more than one reference to rows in the other table!
                while (triggerPtrQuery.next()) {
                    QString tableO=triggerPtrQuery.value(triggerPtrQuery.record().indexOf(tr("table"))).toString();
                    size_t fieldO=triggerPtrQuery.value(triggerPtrQuery.record().indexOf(tr("field"))).toInt();
                    QString formO=triggerPtrQuery.value(triggerPtrQuery.record().indexOf(tr("form_name"))).toString();
                    size_t mapperO=triggerPtrQuery.value(triggerPtrQuery.record().indexOf(tr("mapper"))).toInt();
                    if (!standardRuleInsertion(rule,id,cellShrPtr(new cell(table,field,form,mapper,cellShrPtr(new cell(tableO,fieldO,formO,mapperO)))),mapPreTriggers)) return false;
                 }

            }else return false;
        }

    QSqlQuery dumPtrQuery;
    if (!dumPtrQuery.prepare(
        "SELECT dbo.UI_Rule_Ptrs.[table], dbo.UI_Rule_Ptrs.field,dbo.UI_Rule_Ptrs.ID , dbo.UI_Rule_Ptrs.mapper, "
        "UI_Forms.Name as form_name FROM UI_Rule_Ptrs "
        "INNER JOIN UI_Forms ON UI_Rule_Ptrs.form=UI_Forms.ID "
        " WHERE (dbo.UI_Rule_Ptrs.id_rules =:id AND dbo.UI_Rule_Ptrs.active=1)"
        )){
            return false;
        }
    dumPtrQuery.bindValue(tr(":id"), naId);
        //Ptrs with no rule are also stored in the references map, so that
        //we can access them later;
     dumPtrQuery.setForwardOnly(true);
     if (!dumPtrQuery.exec()) return false;

/*
     //Force also this query query
     while(dumPtrQuery.numRowsAffected()<1)
        if (!dumPtrQuery.exec()) return false;

#ifdef _DEBUG
     test(dumPtrQuery.numRowsAffected());
#endif
*/
     while (dumPtrQuery.next()){
        QString tableO=dumPtrQuery.value(dumPtrQuery.record().indexOf(tr("table"))).toString();
        size_t fieldO=dumPtrQuery.value(dumPtrQuery.record().indexOf(tr("field"))).toInt();
        size_t idO=dumPtrQuery.value(dumPtrQuery.record().indexOf(tr("ID"))).toInt();
        QString formO=dumPtrQuery.value(dumPtrQuery.record().indexOf(tr("form_name"))).toString();
        size_t mapperO=dumPtrQuery.value(dumPtrQuery.record().indexOf(tr("mapper"))).toInt();
        mapReferences.insert(idO,cellShrPtr(new cell(tableO,fieldO,formO,mapperO)));
     }

    }
    //else //TODO: handle this prob later!!!
        //buildHashes();//Sometimes the query returns -1 (QOdbc prob): let's force it again!

/*
#ifdef _DEBUG
    test(mapPreTriggers);//n.b.: in this test we are assuming there is *at least* one trigger reference in the database!
    test(mapReferences);//n.b.: in this test we are assuming there is *at least* one rule in the database!
#endif
*/
    return true;
}

void RuleChecker::test(const int num)
{
    QVERIFY(num>0);
}

void RuleChecker::test(MapReferences& map)
{
    QVERIFY(map.size()>0);
}

void RuleChecker::test(MapRules& map)
{
    QVERIFY(map.size()>0);
}

bool RuleChecker::standardRuleInsertion(const QString rule, const size_t id,
                                        cellShrPtr ref, MapRules& ruleMap)
{
    ruleMap.insert(id,rule);
    if (ref.get()!=0)
        mapReferences.insert(id, ref);
    return true;
}

bool RuleChecker::findReference(const int refId, QString& strOutTable, size_t& strOutField, QString& strOutForm, size_t& strOutMapper)
{
    MapReferences::const_iterator it=mapReferences.find(refId);
    if (it!=mapReferences.end())
    {
        strOutTable=it.value().get()->m_strTable;
        strOutField=it.value().get()->m_idxField;
        strOutForm=it.value().get()->m_strForm;
        strOutMapper=it.value().get()->m_idxMapper;
    }
    else return false;

    return true;
}

bool RuleChecker::parseRule(const QString strRule, QList<size_t>& idList, QMultiMap<QString, QMap<size_t,size_t> >& mapLookups)
{
    int left=0,right=0;
    while (left!=-1){
        left=strRule.indexOf(QString(StrRulePtr+ tr("(")),left,Qt::CaseInsensitive);
        if (left==-1) break;
        right=strRule.indexOf(tr(")"),left);
        if (right==0) break;
        //parse number ///////////////
        int start=left+ QString(StrRulePtr+ tr("(")).length();
        int len=right-start;
        int no=strRule.mid(start,len).toInt();
        idList.push_back(no);
        QString strTable,strForm;
        size_t field,mapper;
        if (!findReference(no,strTable,field,strForm,mapper)) return false;
        QMap<size_t,size_t> mapMapper;
        mapMapper.insert(mapper,field);
        mapLookups.insert(strForm,mapMapper);
        left=start+len;//found next occurrence
    }

    return true;
}

bool RuleChecker::applyRule(const QString strRule,QSqlQuery& query, QVariant varPar)
{
    query.prepare(strRule);
    if (varPar.type()!=QVariant::Invalid) {
        // Bind parameter
        query.bindValue(tr(":par"),varPar);
    }
    query.setForwardOnly(true);
    return query.exec();
}

////////////////////////

InitRulesThread::InitRulesThread(RuleChecker* parent)
{
        rulesPtr=parent;
        moveToThread(this);

        QObject::connect(this,
                       SIGNAL(finished()),
                       this,
                       SLOT(deleteLater()));
}

void InitRulesThread::run()
{
    QTimer::singleShot(0, this, SLOT(doTheWork()));
    exec();
}

void InitRulesThread::doTheWork()
{
    emit done(rulesPtr->init());
}
