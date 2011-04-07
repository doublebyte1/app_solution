#include "buttongroup.h"

ButtonGroup::ButtonGroup(QWidget *parent)
	: QWidget(parent)
{
    m_buttonGroup=new QButtonGroup(this);

    connect(m_buttonGroup, SIGNAL(buttonClicked (int)), this,
    SIGNAL(buttonClicked(int)));

    connect(m_buttonGroup, SIGNAL(buttonReleased(int)), this,
    SIGNAL(buttonReleased(int)));

    connect(m_buttonGroup, SIGNAL(buttonPressed(int)), this,
    SIGNAL(buttonPressed(int)));
}


ButtonGroup::~ButtonGroup()
{
}

int ButtonGroup::getCheckedId()
{
	return m_buttonGroup->checkedId();
}

void ButtonGroup::checkId(int id)
{
    m_buttonGroup->button(id)->setChecked(true);

    //! This is to *force* the clicked event on the RadioButton!
    if (qobject_cast<QRadioButton*>(m_buttonGroup->button(id)))
        qobject_cast<QRadioButton*>(m_buttonGroup->button(id))->click();
}

void ButtonGroup::addButton(QAbstractButton * button, int id)
{
    return m_buttonGroup->addButton(button,id);
}

/////////////////////////////////////
RadioDelegate::RadioDelegate(QWidget *parent)
    : QSqlRelationalDelegate(parent)
{

}
void RadioDelegate::commitMyData()
{
    QWidget *obj = qobject_cast<QWidget*>(sender());

    emit commitData(obj);
    emit closeEditor(obj);
}

/////////////////////////////////////

