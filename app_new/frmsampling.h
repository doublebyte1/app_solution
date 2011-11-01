#include <QtGui>
#include <QtSql>
#include "generictab.h"
#include "ui_frmsampling.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef FRMSAMPLING_H
#define FRMSAMPLING_H

//! Delegate Class
/*!
This class implements acustom delegate for the combo box.
*//*
class Delegate : public QSqlRelationalDelegate 
{
        Q_OBJECT

    public:
        Delegate(QObject *parent = 0);

        void setEditorData(QWidget *editor,
                           const QModelIndex &index) const;
        void setModelData(QWidget *editor,
                          QAbstractItemModel *model,
                          const QModelIndex &index) const;

};*/
///////////////////////////////////////////////////////////////////

//! Custom Model Class
/*!
This class implements an editable relatioanl model, appropriated for defining the characteristics of the sampling process.
*/
class CustomModel : public QSqlRelationalTableModel
{
    Q_OBJECT

    public:

        CustomModel( QObject * parent = 0, QSqlDatabase db = QSqlDatabase() );
        ~CustomModel();

        Qt::ItemFlags flags ( const QModelIndex & index ) const;

};

///////////////////////////////////////////////////////////////////////

//! Frm Frame Sampling Class
/*!
This class implements the widget that allows us to define the properties of each stage of the sampling process.
*/

class FrmSampling : public QWidget, public Ui::FrmSampling
{
    Q_OBJECT

    public:

        FrmSampling(Sample* inSample, QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmSampling();

    public slots:

    signals:
        void                           hideFrmSampling(bool bNotSubmitted);
        void                           showStatus(QString str);//!< signal for showing messages in the status bar
        void                           showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages

    protected:
        void                           showEvent ( QShowEvent * event );

    private slots:
        void                           back();
        void                           apply();
        void                           initRecords(int index);

    private:
        void                           setTips(const bool bLogbook);
        void                           initTable();
        void                           initModels();
        void                           initUI();
        bool                           m_submitted;
        QSqlTableModel*                tRefSchema;
        QSqlTableModel*                tRefLevels;
        CustomModel*                   tSampLevels;
        Sample*                        m_sample;/**< pointer to the Sample structure, hosted on the main form */
};

#endif //FRMSAMPLING_H

