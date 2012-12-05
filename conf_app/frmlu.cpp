#include "frmlu.h"

frmlu::frmlu(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
}
frmlu::~frmlu()
{

}

bool frmlu::checkID()
{
    QSqlDatabase db=QSqlDatabase::database();
     QSqlQueryModel *model = new QSqlQueryModel;
     model->setQuery("SELECT ID from info_changes where ID=" +
         QVariant(this->spinBox->value()).toString());

     return model->rowCount()==1;
}

void frmlu::emitLU()
{
    if (!checkID()){
        QMessageBox msgBox(QMessageBox::Critical,tr("Database Error"),
        tr("Could not find this ID in the database!"),QMessageBox::Ok,0);
        msgBox.exec();
        show();
        return;
    }
    emit LU(this->spinBox->value());
}