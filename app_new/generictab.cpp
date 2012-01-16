#include <QTest>
#include "generictab.h"

GenericTab::GenericTab(const int index, RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_index(index), m_tDateTime(inTDateTime), m_roleDef(inRoleDef), m_sample(inSample), m_title(inStrTitle), m_ruleCheckerPtr(ruleCheckerPtr) {

    lbHead=0;
    m_mapperBinderPtr=0;
    nullDellegate=0;
//     m_helpEngine = 0;

    connect(this, SIGNAL(lockControls(bool,QList<QWidget*>&)), this,
    SLOT(onLockControls(bool,QList<QWidget*>&)));

    connect(this, SIGNAL(forward(QString)), this,
    SLOT(goForward()));

    this->setFocusPolicy(Qt::StrongFocus);
    //initHelp();
    //connectHelpIds();
}

GenericTab::~GenericTab()
{
    if (nullDellegate!=0) delete nullDellegate;
    if (m_mapperBinderPtr!=0) delete m_mapperBinderPtr;
    //if (m_helpEngine!=0) delete m_helpEngine;
}

/*
void GenericTab::focusOutEvent ( QFocusEvent * event )
{

}

void GenericTab::connectHelpIds()
{
    for (int i=0; i < this->children().size(); ++i)
    {
        if (qobject_cast<QWidget *>(this->children().at(i))!=0){

        connect(qobject_cast<QWidget *>(this->children().at(i)), SIGNAL(addRecord()), mapperBinderPtr,
            SIGNAL(addRecord()));

            
        }
    }

}

/*
void GenericTab::initHelp()
{
     QString collectionFile = QDir::toNativeSeparators(QDir::currentPath()) + QDir::separator()
    + QLatin1String("mycollection.qhc");

     m_helpEngine = new QHelpEngineCore(collectionFile, this);
     if (!m_helpEngine->setupData()) {
         delete m_helpEngine;
         m_helpEngine = 0;
     }
}
/*
void GenericTab::showHelpForKeyword(const QString &id)
{
     if (m_helpEngine) {
         QMap<QString, QUrl> links = m_helpEngine->linksForIdentifier(id);
         if (links.count())
             setSource(links.constBegin().value());
     }
}
*/
/*
QVariant GenericTab::loadResource(int type, const QUrl &name)
 {
     QByteArray ba;
     if (type < 4 && m_helpEngine) {
         QUrl url(name);
         if (name.isRelative())
             url = source().resolved(url);
         ba = m_helpEngine->fileData(url);
     }
     return ba;
}
*/

bool GenericTab::initBinder(MapperRuleBinder* mapperBinderPtr)
{
    // initialize rule binder and *connect* signals!! (on init())
    //m_mapperBinderPtr=new MapperRuleBinder(m_ruleCheckerPtr, mapper);
    mapperBinderPtr->init();

    //! This is are the signals of the rule binder we need to connect to:
    // addRecord, first stage record added and second stage record added (run and finish running post-triggers)
    // the pre triggers signals are connected in the binder classes; then we just need the stuff to show messages...

    // Default Rules
    connect(this, SIGNAL(addRecord()), mapperBinderPtr,
        SIGNAL(addRecord()));

    // Pre Submit Rules
    connect(this, SIGNAL(submit()), mapperBinderPtr,
        SIGNAL(submitRecord()));

    connect(mapperBinderPtr, SIGNAL(finishedPreSubmit(const bool)), this,
        SLOT(onPreSubmit(const bool)));

    // Messages
    connect(mapperBinderPtr, SIGNAL(showError(QString, const bool)), this,
    SIGNAL(showError(QString, const bool)));

    connect(mapperBinderPtr, SIGNAL(showStatus(QString)), this,
        SIGNAL(showStatus(QString)));

    return true;
}

void GenericTab::apply()
{
    emit submit();
}

void GenericTab::onPreSubmit(const bool bSubmit)
{
    if (bSubmit) IReallyApply();
}

void GenericTab::setLbHead(QLabel* inLbHeader)
{
    lbHead=inLbHeader;
}

bool GenericTab::getDtId(const int mapIdx, int& id)
{
    QModelIndex idx= m_tDateTime->index(mapIdx,0,QModelIndex());
    if (!idx.isValid()) return false;

    id=m_tDateTime->data(idx).toInt();
    return true;
}

void GenericTab::goBack()
{
    emit navigate(false,m_index);
}

void GenericTab::goForward()
{
    emit navigate(true,m_index);
}

void GenericTab::onLockControls(bool bLock,QList<QWidget*>& lWidgets)
{
    for (int i=0; i < lWidgets.size();++i)
        lWidgets.at(i)->setDisabled(bLock);
}

///////////////////////////////////////////////

NullRelationalDelegate::NullRelationalDelegate(QList<int> colsOthers, QList<int> colsText, QObject *parent):
                        QSqlRelationalDelegate(parent),m_colsText(colsText), m_colsOthers(colsOthers)
{

}
void NullRelationalDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){
        QSqlRelationalDelegate::setModelData(editor,model,index);
    }else{
        if (m_colsText.contains(index.column())){//textEdits
            model->setData(index, editor->property("plainText") == tr("") ?
                QVariant() :
            editor->property("plainText"));
        }else {
            model->setData(index, editor->property("text") == tr("") ?
            QVariant() :
            editor->property("text"));
        }
    }
}

void NullRelationalDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (m_colsOthers.contains(index.column())){//others
        QSqlRelationalDelegate::setEditorData(editor,index);
    }else{
        if (m_colsText.contains(index.column())){//text edits
            editor->setProperty("plainText", index.data());
        }else {
            editor->setProperty("text", index.data());
        }
    }
}
//////////////////////////////////////////////////////////////////////

SecondaryFrm::SecondaryFrm(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

}


////////////////////////////////////////// static

void filterTable(QSqlTableModel* table)
{
    table->setFilter("Name<>'" + qApp->translate("null_replacements", strNa)
            + "' AND Name<>'" + qApp->translate("bin", strOutside)
            + "' AND Name<>'" + qApp->translate("null_replacements", strMissing)
            + "' AND Name<>'" + qApp->translate("null_replacements", strOther)
            + "' AND Name<>'" + qApp->translate("null_replacements", strUnknown)
            + "'");
}

void resizeToVisibleColumns ( QTableView* table )
{
    int ct=0;
    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i)) ++ ct;

    for (int i=0; i < table->model()->columnCount(); ++i)
        if (!table->isColumnHidden(i))
            table->setColumnWidth(i,table->width()/ct);

}
//////////////////////////////////////////////////

bool Sample::setMemberById(const int id, const int val)
{
         switch (id) {
           case 0:
                frameTimeId=val;
                break;
           case 1:
                minorStrataId=val;
               break;
           case 2:
                cellId=val;
                break;
           case 3:
                vesselTypeId=val;
                break;
           case 4:
                sampVesselId=val;
                break;
           case 5:
                tripId=val;
                break;
           case 6:
                operationId=val;
                break;
           case 7:
                catchId=val;
                break;
           default:
               // should never be reached
               return false;
               break;
         }

         return true;
}
