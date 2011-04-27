#include <QDebug>
#include <QtSql>
#include "modelinterface.h"
#include "globaldefs.h"

ModelInterface::ModelInterface (QObject *parent):
QObject(parent)
{
    initModels();
}

ModelInterface::ModelInterface (TreeModel* aTreeModel, QObject *parent):
QObject(parent),treeModel(aTreeModel)
{
    tRefFrame=0;
    tSubFrame=0;
    tRefGLS=0;
    tRefLS=0;
    tRefVessels=0;
    tLinkFr2GLS=0;
    tLinkGLS2LS=0;
    tLinkLS2Vessels=0;
    tChangesPermVessel=0;
    tChangesPermLS=0;
    tChangesPermGLS=0;
    initModels();
}

void ModelInterface::initModels()
{
    if (tRefFrame!=0) delete tRefFrame;
    tRefFrame=new QSqlRelationalTableModel;
    tRefFrame->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("FR_Frame"),
        QSqlDriver::TableName));
    tRefFrame->setRelation(5, QSqlRelation(tr("Ref_Source"), tr("ID"), tr("Name")));
    filterTable(tRefFrame->relationModel(5));

    tRefFrame->setRelation(4, QSqlRelation(tr("FR_Frame"), tr("ID"), tr("Name")));
    tRefFrame->setEditStrategy(QSqlTableModel::OnManualSubmit);
    tRefFrame->select();
    vTables << tRefFrame;

    if (tSubFrame!=0) delete tSubFrame;
    tSubFrame=new QSqlTableModel();
    if (tRefGLS!=0) delete tRefGLS;
    tRefGLS=new QSqlTableModel();
    if (tRefLS!=0) delete tRefLS;
    tRefLS=new QSqlTableModel();
    if (tRefVessels!=0) delete tRefVessels;
    tRefVessels=new QSqlTableModel();
    if (tLinkFr2GLS!=0) delete tLinkFr2GLS;
    tLinkFr2GLS=new QSqlTableModel();
    if (tLinkGLS2LS!=0) delete tLinkGLS2LS;
    tLinkGLS2LS=new QSqlTableModel();
    if (tLinkLS2Vessels!=0) delete tLinkLS2Vessels;
    tLinkLS2Vessels=new QSqlTableModel();
    if (tChangesPermVessel!=0) delete tChangesPermVessel;
    tChangesPermVessel=new QSqlTableModel();
    if (tChangesPermLS!=0) delete tChangesPermLS;
    tChangesPermLS=new QSqlTableModel();
    if (tChangesPermGLS!=0) delete tChangesPermGLS;
    tChangesPermGLS=new QSqlTableModel();

    initModel(tSubFrame,tr("FR_Sub_Frame"));
    initModel(tRefGLS,tr("Ref_Group_of_LandingSites"));
    filterTable(tRefGLS);
    initModel(tRefLS,tr("Ref_Abstract_LandingSite"));
    filterTable(tRefLS);
    initModel(tRefVessels,tr("Ref_Vessels"));
    filterTable(tRefVessels);
    initModel(tLinkFr2GLS,tr("FR_F2GLS"));
    initModel(tLinkGLS2LS,tr("FR_GLS2ALS"));
    initModel(tLinkLS2Vessels,tr("FR_ALS2Vessel"));
    initModel(tChangesPermVessel,tr("Changes_Perm_Vessel"));
    initModel(tChangesPermLS,tr("Changes_Perm_LS"));
    initModel(tChangesPermGLS,tr("Changes_Perm_GLS"));

}

bool ModelInterface::filterTables()
{
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
        filterTable(*it);
    }
    return true;
}

bool ModelInterface::initModel(QSqlTableModel* model, const QString strTable)
{
    model->setTable(strTable);
    model->select();
    vTables << model;

    return true;
}

ModelInterface::~ModelInterface()
{
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
         if ((*it)!=0) delete (*it);
    }
}

bool ModelInterface::writeModel()
{
    return writeTables();
}

bool ModelInterface::insertNewRecord(QSqlTableModel* model)
{
   return model->insertRow(model->rowCount());
}

bool ModelInterface::writeFr2GLS(const int FrameId, const QVector<int>& vId)
{
    QVector<int>::const_iterator it;
    for (it = vId.begin(); it != vId.end(); ++it){

        if (!tLinkFr2GLS->insertRow(tLinkFr2GLS->rowCount()))
            return false;

        QModelIndex idx=tLinkFr2GLS->index(tLinkFr2GLS->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!tLinkFr2GLS->setData(idx,FrameId)) return false;//id frame

        idx=tLinkFr2GLS->index(tLinkFr2GLS->rowCount()-1,2);
        if (!idx.isValid()) return false;
        if (!tLinkFr2GLS->setData(idx,*it)) return false;//id gls

        if (!tLinkFr2GLS->submitAll())
            return false;

    }

    return true;
}

bool ModelInterface::writeGLS2LS(const int FrameId, const int GLSId, const QVector<int>& vId)
{
    QVector<int>::const_iterator it;
    for (it = vId.begin(); it != vId.end(); ++it){

        if (!tLinkGLS2LS->insertRow(tLinkGLS2LS->rowCount()))
            return false;

        QModelIndex idx=tLinkGLS2LS->index(tLinkGLS2LS->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!tLinkGLS2LS->setData(idx,FrameId)) return false;//id frame

        idx=tLinkGLS2LS->index(tLinkGLS2LS->rowCount()-1,2);
        if (!idx.isValid()) return false;
        if (!tLinkGLS2LS->setData(idx,GLSId)) return false;//id gls

        idx=tLinkGLS2LS->index(tLinkGLS2LS->rowCount()-1,3);
        if (!idx.isValid()) return false;
        if (!tLinkGLS2LS->setData(idx,*it)) return false;//id ls

        if (!tLinkGLS2LS->submitAll())
            return false;

    }

    return true;
}

bool ModelInterface::writeLS2Vessel(const int FrameId, const int lsId, const QVector<int>& vId)
{

    QVector<int>::const_iterator it;
    for (it = vId.begin(); it != vId.end(); ++it){

        if (!tLinkLS2Vessels->insertRow(tLinkLS2Vessels->rowCount()))
            return false;

        QModelIndex idx=tLinkLS2Vessels->index(tLinkLS2Vessels->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!tLinkLS2Vessels->setData(idx,FrameId)) return false;//id frame

        idx=tLinkLS2Vessels->index(tLinkLS2Vessels->rowCount()-1,2);
        if (!idx.isValid()) return false;
        if (!tLinkLS2Vessels->setData(idx,lsId)) return false;//id ls

        idx=tLinkLS2Vessels->index(tLinkLS2Vessels->rowCount()-1,3);
        if (!idx.isValid()) return false;
        if (!tLinkLS2Vessels->setData(idx,*it)) return false;//id vessel

        if (!tLinkLS2Vessels->submitAll())
            return false;

    }

    return true;
}

bool ModelInterface::getIdofGLS(const TreeItem* item, int& id)
{
    if (item->data(4).toInt()!=-1){
        id=item->data(4).toInt();
    }else{

        if (!tRefGLS->insertRow(tRefGLS->rowCount()))
            return false;

        QModelIndex idx=tRefGLS->index(tRefGLS->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!tRefGLS->setData(idx,item->data(0))) return false;//name

        if (!item->data(1).toString().isEmpty()){
            idx=tRefGLS->index(tRefGLS->rowCount()-1,3);
            if (!idx.isValid()) return false;
            if (!tRefGLS->setData(idx,item->data(1))) return false;//description
        }

        if (!item->data(3).toString().isEmpty()){
            idx=tRefGLS->index(tRefGLS->rowCount()-1,4);
            if (!idx.isValid()) return false;
            if (!tRefGLS->setData(idx,item->data(3))) return false;//comment
        }
        if (!tRefGLS->submitAll())
            return false;

        idx=tRefGLS->index(tRefGLS->rowCount()-1,0);
        id=tRefGLS->data(idx).toInt();
    }

    return true;
}

bool ModelInterface::genericInsertChanges(const TreeItem* item, const int itemId, const int frameId, QSqlTableModel * model)
{
    //if we have reasons, write them
    if (!item->data(5).toString().isEmpty()){

        if (!model->insertRow(model->rowCount()))
            return false;

        QModelIndex idx=model->index(model->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!model->setData(idx,frameId)) return false;//id_frame

        idx=model->index(model->rowCount()-1,2);
        if (!idx.isValid()) return false;
        if (!model->setData(idx,itemId)) return false;//id

        idx=model->index(model->rowCount()-1,3);
        if (!idx.isValid()) return false;

        if (static_cast<TreeModel::Level>(item->data(2).toInt())==TreeModel::VS){
            int id;
            if (!getIdofReason(item->data(5).toString(),id))
                return false;
            if (!model->setData(idx,id)) return false;//reason
        }else
            if (!model->setData(idx,item->data(5))) return false;//reason

        if (!model->submitAll())
            return false;
    }

    return true;
}

bool ModelInterface::getIdofLS(const TreeItem* item, int& id)
{
    if (item->data(4).toInt()!=-1){
        id=item->data(4).toInt();
    }else {

        if (!tRefLS->insertRow(tRefLS->rowCount()))
            return false;

        //for now, we only give support for adding virtual ports
        //3,17,8
        QModelIndex idx=tRefLS->index(tRefLS->rowCount()-1,1);
        if (!idx.isValid()) return false;
        if (!tRefLS->setData(idx,3)) return false;//type

        idx=tRefLS->index(tRefLS->rowCount()-1,2);
        if (!idx.isValid()) return false;
        if (!tRefLS->setData(idx,17)) return false;//port

        idx=tRefLS->index(tRefLS->rowCount()-1,3);
        if (!idx.isValid()) return false;
        if (!tRefLS->setData(idx,8)) return false;//collector

        idx=tRefLS->index(tRefLS->rowCount()-1,4);
        if (!idx.isValid()) return false;
        if (!tRefLS->setData(idx,item->data(0))) return false;//name

        if (!item->data(1).toString().isEmpty()){
            idx=tRefLS->index(tRefLS->rowCount()-1,6);
            if (!idx.isValid()) return false;
            if (!tRefLS->setData(idx,item->data(1))) return false;//description
        }

        if (!item->data(3).toString().isEmpty()){
            idx=tRefLS->index(tRefLS->rowCount()-1,7);
            if (!idx.isValid()) return false;
            if (!tRefLS->setData(idx,item->data(3))) return false;//comment
        }

        if (!tRefLS->submitAll())
            return false;

        idx=tRefLS->index(tRefLS->rowCount()-1,0);
        id=tRefLS->data(idx).toInt();
    }
    return true;
}

bool ModelInterface::getIdofSubFrameType(const QString strType, int& id)
{
    QSqlQuery query;
    query.prepare(
    tr("SELECT     ID")+
    tr(" FROM         Ref_Frame")+
    tr(" WHERE     (Name = :name)")
    );

    query.bindValue(0, strType);

    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;//It must *always* find an id

    query.first();
    id=query.value(0).toInt();

    return true;
}

bool ModelInterface::getIdofBin(const QString strTable, int& id)
{
    QSqlQuery query;
    QString queryStr=
    tr("SELECT     ID")+
    tr(" FROM         [table]")+
    tr(" WHERE     (Name = :bin)")
    ;

    queryStr.replace(tr("[table]"),strTable);
    query.prepare(queryStr);

    query.bindValue(0, qApp->translate("bin", strOutside));

    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;//It must *always* find an id

    query.first();
    id=query.value(0).toInt();

    return true;
}

bool ModelInterface::getIdofReason(const QString strReason, int& id)
{
    QSqlQuery query;
    query.prepare(
    tr("SELECT     ID")+
    tr(" FROM         Ref_Changes")+
    tr(" WHERE     (Name = :name)")
    );

    query.bindValue(0, strReason);

    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;//It must *always* find an id

    query.first();
    id=query.value(0).toInt();

    return true;
}

bool ModelInterface::getIdofVessel(const TreeItem* item, int& id)
{
    if (item->data(4).toInt()==-1) return false;

    QSqlQuery query;
    query.prepare(
    tr("SELECT     VesselID")+
    tr(" FROM         Ref_Vessels")+
    tr(" WHERE     (VesselID = :id)")
    );

    query.bindValue(0, item->data(4));

    if (!query.exec()) return false;
    if (query.numRowsAffected()<1) return false;//It must *always* find the Vessel ID!

    query.first();
    id=query.value(0).toInt();

    return true;
}

bool ModelInterface::writeManyVessels(TreeItem* item, const int lsId, const int frameId)
{
    QVector<int> vId;
    for (int i=0; i < item->childCount(); ++i){

        if (!writeVessel(item->child(i),lsId,frameId,vId))
            return false;
    }

    return writeLS2Vessel(frameId,lsId,vId);
}

bool ModelInterface::writeVessel(TreeItem* item, const int lsId, const int frameId, QVector<int>& vId)
{
    int vesselId;
    if (!getIdofVessel(item,vesselId))
        return false;
    vId << vesselId;

    if (!genericInsertChanges(item,vesselId,frameId,tChangesPermVessel))
        return false;

    return true;
}

bool ModelInterface::writeManyLS(TreeItem* item, const int glsId, const int frameId)
{
    QVector<int> vId;
    for (int i=0; i < item->childCount(); ++i){

        if (!writeLS(item->child(i),glsId,frameId,vId)) return false;

    }

    return writeGLS2LS(frameId,glsId,vId);
}

bool ModelInterface::writeLS(TreeItem* item, const int glsId, const int frameId, QVector<int>& vId)
{
    int lsId;
    if (!getIdofLS(item,lsId))
        return false;
    vId << lsId;
    if (!writeManyVessels(item, lsId, frameId))
        return false;

    if (!genericInsertChanges(item,lsId,frameId,tChangesPermLS))
        return false;

    return true;
}

bool ModelInterface::writeBin(TreeItem* item, const int id)
{
    for (int i=0; i < item->childCount(); ++i){
        if (static_cast<TreeModel::Level>(item->child(i)->data(2).toInt())==TreeModel::GLS){

            QVector<int> vId;
            if (!writeGLS(item->child(i),id,vId))
                return false;
            if (!writeFr2GLS(id,vId)) return false;

        }else if (static_cast<TreeModel::Level>(item->child(i)->data(2).toInt())==TreeModel::LS){

            int glsBinId;
            if (!getIdofBin(tr("Ref_Group_of_LandingSites"),glsBinId))
                return false;
            QVector<int> vId;
            if (!writeLS(item->child(i),glsBinId,id, vId))
                return false;
            if (!writeGLS2LS(id,glsBinId,vId)) return false;

        }else if (static_cast<TreeModel::Level>(item->child(i)->data(2).toInt())==TreeModel::VS){

            int lsBinId;//=34;
            if (!getIdofBin(tr("Ref_Abstract_LandingSite"),lsBinId))
                return false;
            QVector<int> vId;
            if (!writeVessel(item->child(i),lsBinId,id,vId)) return false;
            if (!writeLS2Vessel(id,lsBinId,vId)) return false;

        } else
            return false;//n.b.: it should never come here!
        }
    return true;
}

bool ModelInterface::writeManyGLS(TreeItem* item, const int id)
{
    QVector<int> vId;
    for (int i=0; i < item->childCount(); ++i){
        if (!writeGLS(item->child(i),id,vId))
            return false;
    }

    return writeFr2GLS(id,vId);
}

bool ModelInterface::writeGLS(TreeItem* item, const int id, QVector<int>& vId)
{
    int glsId;
    if (!getIdofGLS(item,glsId))
        return false;
    vId << glsId;

    if (!writeManyLS(item, glsId, id))
        return false;

    if (!genericInsertChanges(item,glsId,id,tChangesPermGLS))
        return false;

    return true;
}

bool ModelInterface::insertSubFrame(const QString str, const int frameId, int& id)
{
    if (!insertNewRecord(tSubFrame)) return false;

    QModelIndex sIdx=tSubFrame->index(tSubFrame->rowCount()-1,1);
    if (!sIdx.isValid()) return false;
    int type;
    if (!getIdofSubFrameType(str,type)) return false;
    if (!tSubFrame->setData(sIdx,type)) return false;//type

    sIdx=tSubFrame->index(tSubFrame->rowCount()-1,4);
    if (!sIdx.isValid()) return false;
    if (!tSubFrame->setData(sIdx,frameId)) return false;//id frame

    sIdx=tSubFrame->index(tSubFrame->rowCount()-1,2);
    if (!sIdx.isValid()) return false;
    if (!tSubFrame->setData(sIdx,str)) return false;//description

    if (!tSubFrame->submitAll()) return false;

    sIdx=tSubFrame->index(
        tSubFrame->rowCount()-1,0);

    if (!sIdx.isValid()) return false;
    id=sIdx.data().toInt();

    return true;
}

bool ModelInterface::writeTables()
{
    //first write the frame
    if (!tRefFrame->submitAll())
        return false;

    // and grab the id...
    QModelIndex idx=tRefFrame->index(
        tRefFrame->rowCount()-1,0);

    if (!idx.isValid()) return false;

    int frameId=idx.data().toInt();

    TreeItem* root=treeModel->root();

    for (int i=0; i < root->childCount(); ++i){
        if (root->child(i)->data(0).toString().compare(
                qApp->translate("bin", strBin)
                , Qt::CaseInsensitive)!=0)//does not compare
        {

            int subFrameId;
            if (!insertSubFrame(qApp->translate("frame", strRoot),frameId,subFrameId)) return false;
            if (!writeManyGLS(root->child(i), subFrameId))
                return false;

        }else{//bin
            int subFrameId;
            if (!insertSubFrame(qApp->translate("bin", strOutside),frameId,subFrameId)) return false;
            if (!writeBin(root->child(i), subFrameId))
                return false;
        }
    }
    return true;
}

void ModelInterface::removeFilters()
{
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
         (*it)->setFilter(tr(""));
    }
}

bool ModelInterface::submitAll()
{
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
        (*it)->submitAll();
    }
    return true;
}

bool ModelInterface::revertAll()
{
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
        (*it)->revertAll();
    }
    return true;
}

bool ModelInterface::getErrors(QString& strError)
{
    strError=tr("");//initialize
    QVector<QSqlTableModel*>::iterator it;
    for (it = vTables.begin(); it != vTables.end(); ++it){
        if ((*it)->lastError().type()!=QSqlError::NoError){
            if (it!=vTables.begin()) strError.append( tr(" AND ") );
            strError.append((*it)->lastError().text());
        }
    }
    return !strError.isEmpty();
}

bool ModelInterface::rollback(const bool bSubmitted)
{
    //if it was submited just remove the last frame and cascades will take care of everything!
    //otherwise rollbak

    return (bSubmitted? tRefFrame->removeRow(tRefFrame->rowCount()-1) &&
        tRefFrame->submitAll(): revertAll());
}

bool ModelInterface::readOneGLS(const int inRow, const int outRow, const QModelIndex& parent, const bool bBin, QModelIndex& cIndex)
{
    treeModel->insertRow(outRow,parent);

    if (!mapData(inRow,outRow,1,0,parent,tRefGLS))
        return false;//Name

    if (!mapData(inRow,outRow,3,1,parent,tRefGLS))
        return false;//Description

    if (!mapData(inRow,outRow,4,3,parent,tRefGLS))
        return false;//Comments

    if (!mapData(inRow,outRow,0,4,parent,tRefGLS))
        return false;//ID

    QModelIndex gls = treeModel->index(outRow, 2, parent);
    treeModel->setData(gls, QVariant(TreeModel::GLS));//level

    gls = treeModel->index(outRow, 6, parent);
    treeModel->setData(gls, -1);//origin

    gls = treeModel->index(outRow, 7, parent);
    bBin?treeModel->setData(gls, tr(":/app_new/glsd.png"))
        :treeModel->setData(gls, tr(":/app_new/gls.png"));//symb

    cIndex=treeModel->index(outRow, 0, parent);
    return (cIndex.isValid());
}

bool ModelInterface::readRefGLS(const QModelIndex& index, const bool bBin)
{
    for (int i=0; i < tRefGLS->rowCount(); ++i)
    {
        QModelIndex idx;
        if (!readOneGLS(i,i,index,bBin,idx)) return false;
    }

    return true;
}

bool ModelInterface::readOneLS(const int inRow, const int outRow, const QModelIndex& parent, const bool bBin, QModelIndex& cIndex)
{
    treeModel->insertRow(outRow,parent);

    if (!mapData(inRow,outRow,4,0,parent,tRefLS))
        return false;//Name

    if (!mapData(inRow,outRow,6,1,parent,tRefLS))
        return false;//Description

    if (!mapData(inRow,outRow,7,3,parent,tRefLS))
        return false;//Comments

    if (!mapData(inRow,outRow,0,4,parent,tRefLS))
        return false;//ID

    QModelIndex ls = treeModel->index(outRow, 2, parent);
    treeModel->setData(ls, QVariant(TreeModel::LS));//level

    ls = treeModel->index(outRow, 6, parent);
    treeModel->setData(ls, -1);//origin

    ls = treeModel->index(outRow, 7, parent);
    treeModel->setData(ls, bBin?tr(":/app_new/lsd.png"):
        tr(":/app_new/ls.png"));//symb

    cIndex=treeModel->index(outRow, 0, parent);

    return (cIndex.isValid());
}
bool ModelInterface::readRefLS(const QModelIndex& parent,const bool bBin)
{
    for (int i=0; i < tRefLS->rowCount(); ++i)
    {
        QModelIndex idx;
        if (!readOneLS(i,i,parent,bBin,idx)) return false;
    }

    return true;
}

bool ModelInterface::readOneVS(const int inRow, const int outRow, const bool bBin, const QModelIndex& parent)
{
    treeModel->insertRow(outRow,parent);

    if (!mapData(inRow,outRow,10,0,parent,tRefVessels))
        return false;//Name

    if (!mapData(inRow,outRow,7,3,parent,tRefVessels))
        return false;//Comments

    if (!mapData(inRow,outRow,0,4,parent,tRefVessels))
        return false;//VesselID

    QModelIndex vs = treeModel->index(outRow, 2, parent);
    treeModel->setData(vs, QVariant(TreeModel::VS));//level

    vs = treeModel->index(outRow, 6, parent);
    treeModel->setData(vs, -1);//origin

    vs = treeModel->index(outRow, 7, parent);
    treeModel->setData(vs, bBin?tr(":/app_new/vesseld.png"):
        tr(":/app_new/vessel.png"));//symb

    return true;
}

bool ModelInterface::readRefVS(const QModelIndex& parent, const bool bBin)
{
    for (int i=0; i < tRefVessels->rowCount(); ++i)
    {
        if (!readOneVS(i,i,bBin,parent)) return false;
    }

    return true;
}

bool ModelInterface::readModel(const int frameId)
{
    //Read all the reference tables and put them on the bin
    QModelIndex bin;
    QModelIndex root;
    if (!createRootElements(bin, root))
        return false;

    tSubFrame->setFilter(tr("id_frame=") + QVariant(frameId).toString());

    if (tSubFrame->rowCount()!=2) return false;
    //ATTENTION: type for now is hardcoded - root=1, bin=2!
    for (int i=0; i < tSubFrame->rowCount(); ++i)
    {
        if (tSubFrame->index(i,1).data()==1){
            if (!readRoot(tSubFrame->index(i,0).data().toInt(),root,false)) return false;
        }else{
            if (!readBin(tSubFrame->index(i,0).data().toInt(),bin,true)) return false;
        }
    }

    tSubFrame->setFilter(tr(""));
    return true;
}

bool ModelInterface::readRoot(const int subFrameId, QModelIndex& root, const bool bBin)
{
    return readGenericStructure(subFrameId,root,bBin);
}

bool ModelInterface::readGenericStructure(const int subFrameId, QModelIndex& root, const bool bBin)
{
    tLinkFr2GLS->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString());

    if (tLinkFr2GLS->rowCount()<1) return true;//there is nothing on the bin/root

    QString strFilter;
    for (int i=0; i < tLinkFr2GLS->rowCount();++i)
    {
        if (i>0)
            strFilter.append(tr(" OR "));

        strFilter.append(tr("ID=")+tLinkFr2GLS->index(i,2).data().toString());
    }
    tRefGLS->setFilter(strFilter);

    //Read GLS
    for (int i=0; i < tRefGLS->rowCount(); ++i)
    {
        QModelIndex gls;
        if (!readOneGLS(i,i,root,bBin,gls)) return false;
        QModelIndex idx=tRefGLS->index(i,0);
        if (!idx.isValid()) return false;

        tLinkGLS2LS->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString() +
            tr(" AND ") + tr("id_gls=") + idx.data().toString());

        //read LS
        for (int j=0; j < tLinkGLS2LS->rowCount(); ++j)
        {
            tRefLS->setFilter(tr("ID=") + tLinkGLS2LS->index(j,3).data().toString());
            QModelIndex ls;
            if (!readOneLS(0,j,gls,bBin,ls)) return false;

            QModelIndex aIdx=tRefLS->index(0,0);
            if (!aIdx.isValid()) return false;

            tLinkLS2Vessels->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString() +
                tr(" AND ") + tr("id_abstract_landingsite=") + aIdx.data().toString());

            //read Vessel
            for (int k=0; k < tLinkLS2Vessels->rowCount(); ++k)
            {
                tRefVessels->setFilter(tr("VesselId=") + tLinkLS2Vessels->index(k,3).data().toString());
                if (!readOneVS(0,k,bBin,ls)) return false;
            }
        }
    }

    tRefGLS->setFilter(tr(""));
    tLinkFr2GLS->setFilter(tr(""));
    tLinkGLS2LS->setFilter(tr(""));
    tRefLS->setFilter(tr(""));
    tLinkLS2Vessels->setFilter(tr(""));
    tRefVessels->setFilter(tr(""));

    return true;
}

bool ModelInterface::readBin(const int subFrameId, QModelIndex& bin, const bool bBin)
{
    if (!readGenericStructure(subFrameId,bin,true)) return false;

    tLinkGLS2LS->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString());

    //read LS
    for (int j=0; j < tLinkGLS2LS->rowCount(); ++j)
    {
        QModelIndex index=tLinkGLS2LS->index(j,2);
        if (index.data()==1){//TODO: get this value programatically

            tRefLS->setFilter(tr("ID=") + tLinkGLS2LS->index(j,3).data().toString());
            QModelIndex ls;
            if (!readOneLS(0,j,bin,bBin,ls)) return false;

            QModelIndex aIdx=tRefLS->index(0,0);
            if (!aIdx.isValid()) return false;

            tLinkLS2Vessels->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString() +
                tr(" AND ") + tr("id_abstract_landingsite=") + aIdx.data().toString());

            //read Vessel
            for (int k=0; k < tLinkLS2Vessels->rowCount(); ++k)
            {
                tRefVessels->setFilter(tr("VesselId=") + tLinkLS2Vessels->index(k,3).data().toString());
                if (!readOneVS(0,k,bBin,ls)) return false;
            }
        }
    }

    tLinkLS2Vessels->setFilter(tr("id_sub_frame=") + QVariant(subFrameId).toString());

    //read Vessel
    for (int k=0; k < tLinkLS2Vessels->rowCount(); ++k)
    {
        QModelIndex index=tLinkLS2Vessels->index(k,2);
        if (index.data()==34){//TODO: get this value programatically

        tRefVessels->setFilter(tr("VesselId=") + tLinkLS2Vessels->index(k,3).data().toString());
        if (!readOneVS(0,k,bBin,bin)) return false;

        }
    }

    tLinkGLS2LS->setFilter(tr(""));
    tRefLS->setFilter(tr(""));
    tLinkLS2Vessels->setFilter(tr(""));
    tRefVessels->setFilter(tr(""));

    return true;
}

bool ModelInterface::createModel()
{
    //Read all the reference tables and put them on the bin
    QModelIndex bin;
    QModelIndex root;
    if (!createRootElements(bin,root))
        return false;

    if (!readRefGLS(bin))
        return false;
    if (!readRefLS(bin))
        return false;
    if (!readRefVS(bin))
        return false;

    return true;
}

bool ModelInterface::createRootElements(QModelIndex& bin, QModelIndex& root)
{
    //creates sub-frame: root and bin

    QModelIndex _root = treeModel->index(0, 0, QModelIndex());

    treeModel->insertRows(0,2,_root);
    root = treeModel->index(0, 0, _root);
    treeModel->setData(root, QVariant(tr("Root")).toString());
    QModelIndex tId = treeModel->index(0, 1, _root);
    treeModel->setData(tId, QVariant(tr("Frame Root")));
    tId = treeModel->index(0, 2, _root);
    treeModel->setData(tId, QVariant(TreeModel::ROOT));
    tId = treeModel->index(0, 7, _root);
    treeModel->setData(tId, tr(":/app_new/exec.png"));

    bin = treeModel->index(1, 0, _root);
    treeModel->setData(bin, QVariant(tr("Bin")).toString());
    tId = treeModel->index(1, 1, _root);
    treeModel->setData(tId, QVariant(tr("Root Recycle Bin")));
    tId = treeModel->index(1, 2, _root);
    treeModel->setData(tId, QVariant(TreeModel::ROOT));
    tId = treeModel->index(1, 7, _root);
    treeModel->setData(tId, tr(":/app_new/trashcan.png"));

    return true;
}

bool ModelInterface::mapData(const int inRow, const int outRow, const int cIn, const int cOut, const QModelIndex& parent,
                              QSqlTableModel* tModel)
{
    QModelIndex mIdx = treeModel->index(outRow, cOut, parent);
    if (!mIdx.isValid()) return false;
    QModelIndex tIdx = tModel->index(inRow, cIn);
    if (!tIdx.isValid()) return false;
    treeModel->setData(mIdx, tIdx.data());

    return true;
}
////////////////////////////////////////// static

void filterTable(QSqlTableModel* table)
{
    table->setFilter(QObject::tr("Name<>'") + qApp->translate("null_replacements", strNa)
            + QObject::tr("' AND Name<>'") + qApp->translate("bin", strOutside)
            + QObject::tr("' AND Name<>'") + qApp->translate("null_replacements", strMissing)
            + QObject::tr("' AND Name<>'") + qApp->translate("null_replacements", strOther)
            + QObject::tr("'"));
}
