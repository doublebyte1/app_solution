#include "custommsgbox.h"

CustomMsgBox::CustomMsgBox(QWidget *parent)
: QDialog(parent, Qt::WindowSystemMenuHint|Qt::WindowTitleHint)
{
	setupUi(this);

}

CustomMsgBox::~CustomMsgBox()
{
}

void CustomMsgBox::fillDialog(QString strTitle, QString strMessage)
{
	this->setWindowTitle(strTitle);
	this->lbMsg->setText(strMessage);
}
