#include <QTest>
#include "frmsampling.h"
#include "generictab.h"

FrmSampling::FrmSampling(QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags){

    setupUi(this);
    m_submitted=false;
}

FrmSampling::~FrmSampling()
{

}

void FrmSampling::showEvent ( QShowEvent * event )
{
    m_submitted=false;
    pushApply->setEnabled(!m_submitted);
}

void FrmSampling::back()
{
    emit hideFrmSampling(m_submitted);
}

void FrmSampling::apply()
{
    m_submitted=true;
    pushApply->setEnabled(!m_submitted);
}

