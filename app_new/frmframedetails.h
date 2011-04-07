#include <QtGui>
#include <QtSql>
#include "ui_frmframedetails.h"
#include "dragdropmodel.h"
#include "frameview.h"
#include "modelinterface.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

#ifndef FRMFRAMEDETAILS_H
#define FRMFRAMEDETAILS_H

class QTreeView;
class NullRelationalDelegate;

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
                    EDIT /*!< Enum value for editing an existent frame. */
                    };

        //! An enum for assigning the changes on the framedetails form.
        /*! Supported persistence modes are: permanent, temporary.
        */
        enum Persistence { PERMANENT, /*!< permanent changes on the frame. */
                    TEMPORARY /*!< Enum value for temporary changes on the frame. */
                    };

        FrmFrameDetails(QWidget *parent = 0, Qt::WFlags flags = 0);
        ~FrmFrameDetails();

        void                    setFrameDetails(const Mode mode, const Persistence persistence,
            const int frameId);

    public slots:

    signals:
        void                    hideFrameDetails();
        void                    showStatus(QString str);//!< signal for showing messages in the status bar
        void                    showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages

    protected:

    private slots:
        void                    back();
        void                    ok();
        void                    cancel();
        void                    apply();
        void                    verify();
        void                    undo();
        void                    isClonedFromPreviousFrame(QString str);
        void                    enableVerify();

    private:
        Mode                    m_mode;
        Persistence             m_persistence;
        bool                    m_submitted;
        bool                    m_verified;
        FrameView               *treeView;
        DragDropModel           *model;
        ModelInterface          *modelInterface;
        QDataWidgetMapper       *mapper;
        NullRelationalDelegate  *nullDellegate;

        bool                    setupItems(const Mode mode, const int frameId);
        void                    setupModel();
        bool                    initModel(const Mode mode, const int frameId);
        void                    initTree();
        void                    initMapper();
        bool                    readModel();
};

Q_DECLARE_METATYPE( FrmFrameDetails::Mode );
Q_DECLARE_METATYPE( FrmFrameDetails::Persistence );

#endif //FRMFRAMEDETAILS_H