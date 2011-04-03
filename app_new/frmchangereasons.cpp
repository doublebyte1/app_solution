#include <QTest>
#include "frmchangereasons.h"

FrmChangeReasons::FrmChangeReasons(QWidget *parent, Qt::WFlags flags):
QDialog(parent, flags){

    setupUi(this);
    tChanges=0;
    init();
}

FrmChangeReasons::~FrmChangeReasons()
{
    if (tChanges!=0) delete tChanges;
}

void FrmChangeReasons::showEvent ( QShowEvent * event )
{
    textChanges->setVisible(!m_VesselReasons);
    cmbChanges->setVisible(m_VesselReasons);
}

void FrmChangeReasons::init ()
{
    tChanges=new QSqlTableModel;
    tChanges->setTable(QSqlDatabase().driver()->escapeIdentifier(tr("Ref_Changes"),
        QSqlDriver::TableName));
    tChanges->select();

    cmbChanges->setModel(tChanges);
    cmbChanges->setModelColumn(2);

}

bool FrmChangeReasons::getDbIndex(int &id)
{
    QModelIndex start=tChanges->index(0,2);
    QModelIndexList idx=tChanges->match(start,0,cmbChanges->currentText(),Qt::MatchFixedString|Qt::MatchCaseSensitive);
    if (idx.size()!=1)
        return false;

    id=tChanges->index(idx.first().row(),0).data().toInt();
    return true;
}