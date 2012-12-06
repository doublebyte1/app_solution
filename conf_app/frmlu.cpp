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

     int ct=model->rowCount();
     delete model; model=0;
     return ct==1;
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