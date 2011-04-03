#include "frmconnect.h"

FrmConnect::FrmConnect(QWidget *parent, Qt::WFlags flags):
QDialog(parent, flags){

	setupUi(this);
	//clear the values of the lineboxes

    if (QSqlDatabase::drivers().isEmpty())
        QMessageBox::information(this, tr("No database drivers found"),
                                 tr("This app requires at least one Qt database driver. "
                                    "Please check the documentation how to build the "
                                    "Qt SQL plugins."));

    this->cmbDriver->addItems(QSqlDatabase::drivers());
}

FrmConnect::~FrmConnect()
{

}

void FrmConnect::accept()
{
	emit ok(lineHost->text(),lineDataSource->text(),lineUsername->text(),
         linePassword->text(),lineAlias->text(),cmbDriver->currentText());
}

void FrmConnect::reject()
{
	hide();
}