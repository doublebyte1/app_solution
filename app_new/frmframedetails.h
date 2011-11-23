#include <QtGui>
#include <QtSql>
#include "ui_frmframedetails.h"
#include "dragdropmodel.h"
#include "frameview.h"
#include "frmlegend.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef FRMFRAMEDETAILS_H
#define FRMFRAMEDETAILS_H

class QTreeView;
class NullRelationalDelegate;
struct Sample;
class ModelInterface;

//! Frm Frame Details Class
/*!
This class implements the widget that corresponds to the widget where
we create/edit and view the sampling frame; This Widget contains a frame that can be populated
with a tree or a set of listboxes;
*/

class FrmFrameDetails : public QWidget, public Ui::frmframedetails
{
    Q_OBJECT

    public:
        //! An enum for showing the framedetails form.
        /*! Supported modes for FrameDetails UI are: view, edit and create.
        */
        enum Mode { VIEW, /*!< Enum value for viewing the frame. */
                    CREATE, /*!< Enum value for creating a new frame. */
                    EDIT, /*!< Enum value for editing an existent frame. */
                    NONE
                    };

        //! An enum for assigning the changes on the framedetails form.
        /*! Supported persistence modes are: permanent, temporary.
        */
        enum Persistence { PERMANENT, /*!< permanent changes on the frame. */
                    TEMPORARY/*!< Enum value for temporary changes on the frame. */
                    };

        //! An enum for generic options in this form        */
        enum Options { 
              READ_TMP    = 0x1,/*!< Read also temporary changes on the frame. */
              ALLOW_NEW   = 0x2,/*!<Allow new items. */
              CACHE_CHANGES   = 0x4,/*!<Cache changes (for edit mode). */
                    };

        FrmFrameDetails(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmFrameDetails();

        bool                    setFrameDetails(const Mode mode, const Persistence persistence,
            Sample* sample, QList<int>& blackList, const int options);

    public slots:

    signals:
        void                    hideFrameDetails(bool bNotSubmitted);
        void                    showStatus(QString str);//!< signal for showing messages in the status bar
        void                    showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
        void                    AppliedChanges2FrameDetails();

    protected:

    private slots:
        void                    back();
        void                    cancel();
        bool                    apply();
        void                    verify();
        void                    undo();
        void                    isClonedFromPreviousFrame(QString str);
        void                    enableVerify();
        void                    showLegend();
        void                    onApplyChanges2FrameDetails();
        bool                    onNoChanges();

    private:
        Sample*                 m_sample;
        Mode                    m_mode;
        Persistence             m_persistence;
        bool                    m_dirty;
        bool                    m_submitted;
        bool                    m_verified;
        FrameView               *treeView;
        DragDropModel           *model;
        ModelInterface          *modelInterface;
        QDataWidgetMapper       *mapper;
        NullRelationalDelegate  *nullDellegate;
        FrmLegend               *pFrmLegend;

        bool                    setupItems(const Mode mode, const Sample* sample, const int options);
        void                    setupModel();
        bool                    initModel(const Mode mode, const Sample* sample, const int options);
        void                    initTree();
        void                    initMapper();
        bool                    readModel();
        bool                    setTreeReadOnly(const bool bRO);
};

Q_DECLARE_METATYPE( FrmFrameDetails::Mode );
Q_DECLARE_METATYPE( FrmFrameDetails::Persistence );

#endif //FRMFRAMEDETAILS_H