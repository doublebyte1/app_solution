#include <QtGui>
#include <QtSql>
#include "ui_mainfrm.h"
#include "CustomMsgBox.h"
#include "frmframedetails.h"
#include "frmframe.h"
#include "frmminorstrata.h"
#include "frmcell.h"
#include "frmvesseltype.h"
#include "frmvessel.h"
#include "frmtrip.h"
#include "frmoperation.h"
#include "frmprjpage.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

using namespace boost;

//////////////////////////////////////////////////////////////////////
#ifndef MAINFRM_H
#define MAINFRM_H

typedef shared_ptr<CustomMsgBox>                    MsgBoxPtr;

//! Main Frm Class
/*!
This class contains an instantiation of the UI mainFrm class.
It stores pointers for the other UI classes, such as Logbook and for a RuleChecker;
N.b.: all the UI classes instantiated here, should ihnerit ReportWidget, if we want to make use of the print/export functionality!
*/

class MainFrm : public QMainWindow, public Ui::MainWindow
{
    Q_OBJECT

    public:
        MainFrm(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~MainFrm();

    private:
        void                    resetTabs();
        void                    initPreviewTab(PreviewTab* tab);
        void                    initUi();
        void                    updateIndexes(const int from);
        void                    CreateXMLFile(const QString strFileName);

        DateModel               *tDateTime;
        FrmFrame                *pFrmFrame;
        FrmMinorStrata          *pFrmMinorStrata;
        FrmFrameDetails         *pFrmFrameDetails;
        FrmCell                 *pFrmCell;
        FrmVesselType           *pFrmVesselType;
        FrmVessel               *pFrmVessel;
        FrmTrip                 *pFrmTrip;
        FrmOperation            *pFrmOperation;
        FrmPrjPage              *pFrmPrjPage;
        QVector<GenericTab*>    vTabs;
        QList<MsgBoxPtr>        m_listMsgBoxes;//!< container for storing pointers to the messageboxes;
        Sample*                 sSample;
        QToolBar*               toolbar;

    private slots:
        void                    addTab(int idx, bool bOk);
        void                    initTabs();
        void                    navigateThroughTabs(const bool bNext, const int idx);
        void                    showFrameDetails(const FrmFrameDetails::Mode mode, 
                                        const FrmFrameDetails::Persistence persistence,Sample* sample, 
                                        QList<int>& blackList, const FrmFrameDetails::Options options);
        void                    hideFrameDetails();
        void                    statusShow(QString str);
        void                    statusClean(QString str);
        void                    displayError(QString strError, const bool bShowMsgBox);
        void                    cleanupMsgBoxes();
        void                    rearrangeTabs(bool bLogBook);
        void                    aboutThisProject();
        void                    loadFile();
        void                    writeFile();
};
#endif //MAINFRM_H