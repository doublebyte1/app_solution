#include <QTest>
#include "generictab.h"

GenericTab::GenericTab(const int index, QWidget *parent, Qt::WFlags flags):
QWidget(parent, flags),m_index(index){

}

GenericTab::~GenericTab()
{
}


void GenericTab::goBack()
{
    emit navigate(false,m_index);
}

void GenericTab::goForward()
{
    emit navigate(true,m_index);
}
