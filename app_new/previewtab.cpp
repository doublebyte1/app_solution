#include "previewtab.h"

PreviewTab::PreviewTab(const int index, RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, RuleChecker* ruleCheckerPtr, QWidget *parent, Qt::WFlags flags):
GenericTab(index,inRoleDef,inSample,inTDateTime,inStrTitle,ruleCheckerPtr,parent,flags){

    m_model=0;
    m_table=0;
    m_buttonBox=0;
    m_pushNew=0;
    m_pushRemove=0;
    m_pushNext=0;
    m_pushPrevious=0;
    m_groupDetails=0;
    m_bLoading=false;
    m_pushEdit=0;

    //Logbook flow
    mapTablesL.insert("Fr_Time",sTable(qApp->translate("null_replacements", strNa),"Ref_Minor_Strata",true));
    mapTablesL.insert("Ref_Minor_Strata",sTable("id_frame_time","Sampled_Strata_Vessels",true));
    mapTablesL.insert("Sampled_Strata_Vessels",sTable("id_minor_strata","Abstract_Sampled_Vessels",false));
    mapTablesL.insert("Abstract_Sampled_Vessels",sTable("id_sampled_strata_vessels","Sampled_Fishing_Trips",false));
    mapTablesL.insert("Sampled_Fishing_Trips",sTable("id_abstract_sampled_vessels","Sampled_Fishing_Operations",true));
    mapTablesL.insert("Sampled_Fishing_Operations",sTable("id_fishing_trip",qApp->translate("null_replacements", strNa),true));

    //sampling flow
    mapTablesS.insert("Fr_Time",sTable(qApp->translate("null_replacements", strNa),"Ref_Minor_Strata",true));
    mapTablesS.insert("Ref_Minor_Strata",sTable("id_frame_time","Sampled_Cell",true));
    mapTablesS.insert("Sampled_Cell",sTable("id_minor_strata","Sampled_Cell_Vessel_Types",false));
    mapTablesS.insert("Sampled_Cell_Vessel_Types",sTable("id_cell","Sampled_Cell_Vessels",false));
    mapTablesS.insert("Sampled_Cell_Vessels",sTable("id_cell_vessel_types","Abstract_Sampled_Vessels",false));
    mapTablesS.insert("Abstract_Sampled_Vessels",sTable("id_sampled_cell_vessels","Sampled_Fishing_Trips",false));
    mapTablesS.insert("Sampled_Fishing_Trips",sTable("id_abstract_sampled_vessels","Sampled_Fishing_Operations",true));
    mapTablesS.insert("Sampled_Fishing_Operations",sTable("id_fishing_trip",qApp->translate("null_replacements", strNa),true));

    setAttribute( Qt::WA_AlwaysShowToolTips);

    connect(this, SIGNAL(isLogBook 
        (const bool)), this,
            SLOT(setTips(const bool)));

    connect(this, SIGNAL(editLeave(const bool,const bool)), this,
        SLOT(onEditLeave(const bool,const bool)));

}

PreviewTab::~PreviewTab()
{
    //if (m_model!=0) delete m_model;//N.b.: dont delete model here: it does not belong to this class!
}

void PreviewTab::setUIPermissions()
{
    m_pushNew->setVisible(m_roleDef->bNew);
    m_pushEdit->setVisible(m_roleDef->bMod);
    m_pushRemove->setVisible(m_roleDef->bDel);
}
void PreviewTab::setTips(const bool bLogbook)
{
    lbHead->setToolTip(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
    lbHead->setStatusTip(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
    lbHead->setWhatsThis(tr("This is a ") + (bLogbook? tr("logbook"): tr("sampling")) + tr(" frame"));
}

bool PreviewTab::submitDates(QDataWidgetMapper* startMapper, QDataWidgetMapper* endMapper)
{
    bool bError=false;
    if (!startMapper->submit() || !endMapper->submit()){
        if (m_tDateTime->lastError().type()!=QSqlError::NoError)
            emit showError(m_tDateTime->lastError().text());
        else
            emit showError(tr("Could not submit dates(s)!!"));
        bError=true;
    }
    else{
        if (!m_tDateTime->submitAll()){
            if (m_tDateTime->lastError().type()!=QSqlError::NoError)
                emit showError(m_tDateTime->lastError().text());
            else
                emit showError(tr("Could not write DateTime in the database!"));

            bError=true;
        }
    }
    return !bError;
}

bool PreviewTab::submitMapperAndModel(QDataWidgetMapper* aMapper)
{
    //ATTENTION: read instruction for use on declaration!
    bool bError=false;

    if (aMapper->submit()){
        bError=!
            m_model->submitAll();
        if (bError){
            if (m_model->lastError().type()!=QSqlError::NoError)
                emit showError(m_model->lastError().text());
            else
                emit showError(tr("Could not write changes in the database!"));
        }
    }else bError=true;

    return !bError;
}

bool PreviewTab::tableSelect(const int id)
{
    if (m_table==0 || m_table->model()==0) return false;

    QModelIndex start=m_table->model()->index(0,0);
    QModelIndexList list=m_table->model()->match(start,0,id);

    if (list.size()!=1 || !list.at(0).isValid()) return false;

    m_table->scrollTo(list.at(0), QAbstractItemView::EnsureVisible);
    m_table->selectRow(list.at(0).row());

    return m_table->selectionModel()->hasSelection();
}

void PreviewTab::genericUI4NewRecord()
{
    m_groupDetails->setVisible(m_roleDef->bView && !m_groupDetails->isVisible());

    emit lockControls(false,m_lWidgets);

    m_buttonBox->button(QDialogButtonBox::Close)->setVisible(false);
    m_buttonBox->button(QDialogButtonBox::Apply)->setVisible(true);
    m_buttonBox->button(QDialogButtonBox::Apply)->setEnabled(true);

    m_pushEdit->setEnabled(false);
    m_pushRemove->setEnabled(false);

    if (m_pushNext!=0)
        m_pushNext->setEnabled(false);

    if (m_pushPrevious!=0)
        m_pushPrevious->setEnabled(false);
}

bool PreviewTab::onButtonClick(QAbstractButton* button)
{
    if (m_buttonBox==0 || m_groupDetails==0) return false;

    if ( m_buttonBox->buttonRole(button) == QDialogButtonBox::RejectRole)
    {
        m_groupDetails->hide();
        this->m_model->revertAll();
        return true;

    } else if (m_buttonBox->buttonRole(button) == QDialogButtonBox::ApplyRole){

        emit submit();
        return true;
    }
    else return false;
}

void PreviewTab::initPreviewTable(QTableView* aTable, QSqlQueryModel* view)
{
    m_table=aTable;

    m_table->setModel(view);

    connect(m_table->selectionModel(), SIGNAL(selectionChanged 
        (const QItemSelection &, const QItemSelection &)), this,
            SLOT(onItemSelection()));

    connect(m_table->model(), SIGNAL(rowsInserted ( const QModelIndex, int, int)), this,
        SLOT(adjustEnables()));

    connect(m_table->model(), SIGNAL(rowsRemoved ( const QModelIndex, int, int)), this,
        SLOT(adjustEnables()));

    m_table->setAlternatingRowColors(true);
    m_table->verticalHeader()->hide();
    m_table->setSelectionMode(
        QAbstractItemView::SingleSelection);
    m_table->setSelectionBehavior( QAbstractItemView::SelectRows);
    m_table->horizontalHeader()->setClickable(false);
    m_table->horizontalHeader()->setFrameStyle(QFrame::NoFrame);
}

bool PreviewTab::afterApply()
{
    if (m_table==0 || m_model==0)
        return false;

    setPreviewQuery();
    m_model->select();

    while(m_model->canFetchMore())
        m_model->fetchMore();

    QModelIndex cIdx=m_model->index(m_model->rowCount()-1,0);
    if (!cIdx.isValid()) return false;

    m_table->selectRow(0);

    m_buttonBox->button(QDialogButtonBox::Close)->setVisible(true);

    return true;
}

void PreviewTab::resizeEvent ( QResizeEvent * event )
{
    (void) event;
    if (m_table==0) return;
    resizeToVisibleColumns(m_table);
}

void PreviewTab::onShowForm()
{
    beforeShow();

    //Make sure all models are up to date, and without filters
    if (m_model==0) return;
    m_model->select();
    m_tDateTime->select();

    setPreviewQuery();

    if (m_tDateTime==0) return ;

    //filter the relational model
    filterModel4Combo();

    if (m_sample==0 || lbHead==0) return;

    if (!m_bLoading && m_table->model()->rowCount()>0){
        QModelIndex idx=m_table->model()->index(0,0);
        m_table->selectionModel()->setCurrentIndex(idx, QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows);
    }

    if (m_pushNext!=0)
        m_pushNext->setEnabled(m_table->selectionModel()->hasSelection());

    if (m_pushEdit==0 || m_pushRemove==0) return;

    adjustEnables();

     emit isLogBook(m_sample->bLogBook);
}

void PreviewTab::adjustEnables()
{
    if (!m_table || !m_pushEdit || !m_pushRemove) return;

    m_pushEdit->setEnabled(m_table->model()->rowCount()>0);
    m_pushRemove->setEnabled(m_table->model()->rowCount()>0);
}

bool PreviewTab::next()
{
    //retrieve selected index
    if (!m_table->selectionModel()->currentIndex().isValid()){
        emit showError(tr("You must select one item!"));
        return false;
    }

    if (!updateSample()) return false;

    emit forward("");
    return true;
}

bool PreviewTab::getNewHeader(QString& strLabel)
{
    if (!getNextLabel(strLabel)) return false;
    strLabel=(lbHead->text().isEmpty()? strLabel:lbHead->text()+ tr("-> ") + strLabel);
    return true;
}

bool PreviewTab::IReallyApply()
{
        return !m_pushEdit->isChecked()? reallyApply(): applyChanges();
}

bool PreviewTab::editRecord(bool on)
{
    //removing filters
    if (m_model==0) return false;
    if (m_tDateTime==0) return false;
    if (m_pushNew==0) return false;
    if (m_pushEdit==0) return false;
    if (m_pushRemove==0) return false;

    if (!on){

      //lets do this first, and then we decide if we want to turn it off!
       m_pushEdit->setChecked(true);

        QMessageBox msgBox;
        msgBox.setText(tr("You are modifying a record."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();

         switch (ret) {
           case QMessageBox::Save:
               apply();
               return false;
                break;//No need for this!
           case QMessageBox::Discard:
               m_model->revertAll();
               //for the date, we dont need to to anything
               emit editLeave(true,true);
               break;
           case QMessageBox::Cancel:
                m_pushEdit->setChecked(true);
                emit editLeave(false);
                return true;
                break;
           default:
               // should never be reached
               break;
         }

    }else{//Let's force the user to click on the table!
        if (!m_table->selectionModel()->hasSelection() || !m_groupDetails->isVisible()){
            emit showError(tr("You must select an item to edit!"));
            m_pushEdit->setChecked(false);
            return false;
        }
       //lets disable navigation for now
        if (m_pushNext!=0) m_pushNext->setEnabled(false);
        if (m_pushPrevious!=0) m_pushPrevious->setEnabled(false);

        emit editLeave(false);
    }
    m_buttonBox->button(QDialogButtonBox::Close)->setVisible(!on);
    emit lockControls(!on,m_lWidgets);

    return true;
}

bool PreviewTab::translateIndex(const QModelIndex inIdx, QModelIndex& outIdx)
{
    //TODO: query model to find correspondence between the viewindex and the model index
    QModelIndex idx=m_table->model()->index(inIdx.row(),0);
    if (!idx.isValid()){
        emit showError (tr("Could not preview this row!"));
        return false;
    }

    QModelIndex start=m_model->index(0,0);
    QModelIndexList list=m_model->match(start,0,idx.data());

    if (list.count()!=1) return false;
    outIdx=list.at(0);

    return true;
}

void PreviewTab::removeRecord()
{
    if (!m_table->selectionModel()->hasSelection()){
        emit showError(tr("You have not selected any record to remove!"));
        return;
    }

    if (!m_table->selectionModel()->currentIndex().isValid()){
        emit showError(tr("You have not selected a valid record!"));
        return;
    }

    QModelIndex idx;
    if (!translateIndex(m_table->selectionModel()->currentIndex(), idx)){
        emit showError(tr("Could not preview this record!"));
        return;
    }

    QModelIndex idName=m_table->model()->index(m_table->selectionModel()->currentIndex().row(),1);

    QMessageBox msgBox;
    msgBox.setText(tr("You have selected record '") + idName.data().toString() +
        tr("' for deletion."));
    msgBox.setInformativeText(tr("Are you sure you want to remove this record and all its dependants?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();

     switch (ret) {
       case QMessageBox::Yes:

            if ( !m_model->removeRow(idx.row()) ){

                if (m_model->lastError().type()!=QSqlError::NoError)
                    emit showError(m_model->lastError().text());
                else
                    emit showError(tr("Could not remove this record!"));

            }else{
                if (!m_model->submitAll()){

                    if (m_model->lastError().type()!=QSqlError::NoError)
                        emit showError(m_model->lastError().text());
                    else
                        emit showError(tr("Could not remove this record!"));

                }
                else{
                    /*
                    QSqlQuery query;
                    query.prepare("exec reset_all_tables");
                    if (!query.exec())
                    {
                        emit showError(tr("Could not reset tables after removal of ") + m_model->tableName() + tr("!"));
                        return;
                    }*/

                    showStatus(tr("Record successfully removed from the database!"));
                    setPreviewQuery();
                    emit recordRemoved();
                    if (m_table->model()->rowCount()>0) m_table->selectRow(0);//to avoid a selection on a non existent row!
                    else m_groupDetails->hide();
                }
            }

           break;
       case QMessageBox::No:
           return;
           break;
       default:
           // should never be reached
           break;
     }

}

void PreviewTab::genericCreateRecord()
{
    //removing filters
    if (m_model==0) return ;
    if (!m_model->filter().isEmpty()) m_model->setFilter(tr(""));

    if (m_tDateTime==0) return ;
    if (!m_tDateTime->filter().isEmpty()) m_tDateTime->setFilter(tr(""));

    if (!discardNewRecord()) return;

    insertRecordIntoModel(m_model);
}

bool PreviewTab::discardNewRecord()
{
    QModelIndex dirtyIdx=m_model->index(m_model->rowCount()-1,0);

    if (m_model->isDirty(dirtyIdx)){

        QMessageBox msgBox;
        msgBox.setText(tr("You are creating a new record."));
        msgBox.setInformativeText(tr("Are you sure you want to leave and loose all changes?"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();

         switch (ret) {
           case QMessageBox::Yes:
                m_model->revertAll();
                return true;
               break;
           case QMessageBox::No:
                return false;
               break;
           default:
               // should never be reached
               break;
         }
    }

    return true;
}

bool PreviewTab::abstractPreviewRow(QModelIndex index)
{
    //its on a new record
    if (!discardNewRecord()) return false;

    //its on a edit
    if (m_pushEdit->isChecked()){
        m_pushEdit->setChecked(false);
        if (!editRecord(false)) return false;
    }

    this->m_groupDetails->setVisible(m_roleDef->bView && !m_groupDetails->isVisible());

    emit lockControls(true,m_lWidgets);
    m_buttonBox->button(QDialogButtonBox::Apply)->setVisible(false);
    m_buttonBox->button(QDialogButtonBox::Close)->setVisible(true);

    m_pushNew->setEnabled(true);
    m_pushEdit->setEnabled(true);
    m_pushRemove->setEnabled(true);

    //setting the filter
    QModelIndex idx=m_table->model()->index(index.row(),0);
    if (!idx.isValid()){
        return false;
    }

    QString id=idx.data().toString();

    m_model->setFilter(m_model->tableName()+".ID="+id);

    if (m_model->rowCount()!=1)
        return false;

    return true;
}

bool PreviewTab::checkDependantDates(const QString curTable, const QDateTime& curStartDt, const QDateTime& curEndDt, QString strTable, int id,
                                     QString& strError)
{
    return (m_sample->bLogBook?onCheckDependantDates(mapTablesL,strTable,curStartDt, curEndDt,strTable,id, strError):
        onCheckDependantDates(mapTablesS,strTable,curStartDt,curEndDt,strTable,id,strError));
}

bool PreviewTab::updateSample(const QModelIndex& idx)
{
    return (m_sample->setMemberById(m_index,idx.data().toInt()));
}

bool PreviewTab::updateSample()
{
    //check if there is a selection
    if (!m_table->selectionModel()->hasSelection())
        return false;

    //updating the sample structure
    QModelIndex idx=m_table->model()->index(m_table->selectionModel()->currentIndex().row(),0);

    if (!idx.isValid()) return false;
    return updateSample(idx);
}

//////////////////////////////////////////////////////////////

bool insertRecordIntoModel(QSqlTableModel* m)
{
    while(m->canFetchMore())
        m->fetchMore();

    return m->insertRow(m->rowCount());
}

void setSourceText(QLabel* label, const bool bIsLogbook)
{
    label->setStyleSheet(bIsLogbook?
        QObject::tr("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(251, 255, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 218, 71, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.57754 rgba(255, 203, 0, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));font: 75 10pt \"Fixedsys\"")
    : QObject::tr("background-color: qconicalgradient(cx:0, cy:0, angle:135, stop:0 rgba(220, 220, 220, 69), stop:0.375 rgba(255, 255, 0, 69), stop:0.423533 rgba(255, 0, 0, 145), stop:0.45 rgba(247, 255, 0, 208), stop:0.477581 rgba(255, 244, 71, 130), stop:0.518717 rgba(255, 85, 0, 130), stop:0.55 rgba(255, 255, 0, 255), stop:0.573864 rgba(255, 255, 255, 130), stop:0.57754 rgba(255, 255, 255, 130), stop:0.625 rgba(255, 255, 0, 69), stop:1 rgba(255, 255, 0, 69));font: 75 10pt \"Fixedsys\"") );
    label->setText(bIsLogbook? qApp->translate("frame", strLogbook): qApp->translate("frame", strSampling));
}
