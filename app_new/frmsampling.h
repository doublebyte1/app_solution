#include <QtGui>
#include <QtSql>
#include "ui_frmsampling.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef FRMSAMPLING
#define FRMSAMPLING

//! Frm Frame Sampling Class
/*!
This class implements the widget that allows us to define the properties of each stage of the sampling process.
*/

class FrmSampling : public QWidget, public Ui::FrmSampling
{
    Q_OBJECT

    public:

        FrmSampling(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmSampling();

    public slots:

    signals:
        void                    hideFrmSampling(bool bNotSubmitted);
        void                    showStatus(QString str);//!< signal for showing messages in the status bar
        void                    showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages

    protected:
        void                    showEvent ( QShowEvent * event );

    private slots:
        void                    back();
        void                    apply();

    private:
        bool                    m_submitted;
};

#endif //FRMSAMPLING_H