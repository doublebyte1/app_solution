#include <QtGui>
#include <QtSql>
#include "frmframedetails.h"
#include "datemodel.h"
#include "globaldefs.h"
#include "rulechecker.h"
#include "mapperrulebinder.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

void                    filterTable(QSqlTableModel* table);
//! Resize columns to contents
/*! This is an utility function to resize the table, in order to show
the contents of the visible columns.
  \par table pointer to a table;
  \sa getDtId(const int mapIdx, int& id)
*/
void                    resizeToVisibleColumns ( QTableView* table );

//////////////////////////////////////////////////////////////////
#ifndef ROLEDEF_H
#define ROLEDEF_H

//! Role structure
/*!
//This structure encapsulates a role definition, based on the username.
The default is all permissions set to false, but they should be defined in the constructor to match the 
user on table UI_user.
*/

struct RoleDef{
    RoleDef(): bNew(false), bView(false), bMod(false), bDel(false), bRep(false), bAdmin(false){;}
//    bool       setMemberById(const int id, const int val);

    bool        bNew;/**< boolean to indicate if the user can introduce data */
    bool        bView;/**< boolean to indicate if the user can view data */
    bool        bMod;/**< boolean to indicate if the user can modify data */
    bool        bDel;/**< boolean to indicate if the user can remove data */
    bool        bRep;/**< boolean to indicate if the user can use reports */
    bool        bAdmin;/**< boolean to indicate if the user can access administrative tools */
};

#endif //ROLEDEF_H
//////////////////////////////////////////////////////////////////

#ifndef SAMPLE_H
#define SAMPLE_H

//! Sample structure
/*!
This structure encapsulates the data that we want to pass around forms;
The data is the information on the sampling process that defines the current record - i.e.,
a "branch" of the Sampling Tree; the current record is identified by some, or all of the
following parameters: logbook or sampling, frame id, frame time id, minor strata id, cell id,
vessel type id, sampled vessel id, trip id, operation id; we pass this value around in the queries,
and also to the QdataWidgetMapper binder;
*/

struct Sample{
    Sample(): frameId(-1), frameTimeId(-1), minorStrataId(-1), cellId(-1), vesselTypeId(-1), sampVesselId(-1),
    tripId(-1),operationId(-1),catchId(-1){;}

    bool       setMemberById(const int id, const int val);

    bool        bLogBook;/**< boolean to indicate if its logbook (true) or sampling(false) */
    int         frameId;/**< frame id */
    int         frameTimeId;/**< frame time id */
    int         minorStrataId;/**< minor strata id */
    int         cellId;/**< cell id */
    int         vesselTypeId;/**< vessel type id */
    int         sampVesselId;/**< sampled vessel id */
    int         tripId;/**< trip id */
    int         operationId;/**< operation id */
    int         catchId;/**< operation id */
};

#endif /\saMPLE_H

//////////////////////////////////////////////////////////////////
#ifndef NULLRELATIONALDELEGATE_H
#define NULLRELATIONALDELEGATE_H

//! Null Delegate Class
/*!
This class implements a delegate between model and mapper, preventing the controls from going empty;
because of the comboboxes, it has to derived from QSqlRelationalDelegate
*/

class NullRelationalDelegate : public QSqlRelationalDelegate
    {
        Q_OBJECT

        public:
            //! A constructor
            /*!
               In this constructor, we take two lists, one with the indexes that point
               to the base class behaviour, and another one (for text fields) for which we actually
               override the function; in this way, we are able to reuse the Relational SQL
               Delegate for all situations.
              \param colsOthers a STL list with columns that use the base class delegate
              \param colsText a STL list with columns that use special null-handling text delegate
            */
            NullRelationalDelegate (QList<int> colsOthers, QList<int> colsText,
                QObject *parent = 0);

        public:
            void setEditorData(QWidget *editor, const QModelIndex &index) const;
            void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

        private:
            QList<int>         m_colsText;
            QList<int>         m_colsOthers;
};

#endif //NULLRELATIONALDELEGATE_H

//////////////////////////////////////////////////////////////////////
#ifndef GENERICTAB_H
#define GENERICTAB_H

//! Frm Generic Tab Class
/*!
This class implements a generic tab widget; the tabs should ihnerit by this class, so that we can access all its common
body of functions.
*/

class GenericTab : public QWidget
{
    Q_OBJECT

    public:
        GenericTab(const int index, RoleDef* inRoleDef, Sample* inSample, DateModel* inTDateTime, const QString inStrTitle, RuleChecker* ruleCheckerPtr=0,
            QWidget *parent = 0, Qt::WFlags flags = 0);
        ~GenericTab();

        //! Set Header Label
        /*! This function passes a pointer to a QLabel, that is used to present the information
        of whether it is a logbook or sampling form.
        \par inLbHeader pointer to a QLabel;
        \sa setIndex(const int index)
        */
        void                    setLbHead(QLabel* inLbHeader);
        //! Set Index
        /*! This function sets the index of the tab;
        \par index index as integer;
        \sa setLbHead(QLabel* inLbHeader)
        */
        void                    setIndex(const int index){m_index=index;}
        //! Get index
        /*! This function returns the index of the tab;
        \return int index
        \
        \sa title()
        */
        const int               index()const {return m_index;}
        //! Get title
        /*! This function returns the title of the tab;
        \return QString title
        \
        \sa index()
        */
        const QString           title()const {return m_title;}
        Sample*                 getSample() {return m_sample;}

    public slots:
        //! Fill header
        /*! This function, uses the pointer to the header label, to fill it with a string;
          \par str text that we want to display in the label (normally: "logbook" or "Artisanal Fisheries")
        */
        void                    fillHeader(const QString str){lbHead->setText(str);}
        //! Apply
        /*! In reality, this method does nothing more than sending a signal to the rule binder (submit());
        If the validation layer is bypassed (pre-submit rules), than another signal redirects the response
        to the function that *actually* applies the changes!
          \sa reallyApply()
        */
        void                    apply();
        //! A pure virtual member.
        /*! This is the method that is called, when we show the form;
        */
        virtual void            onShowForm()=0;
        //! A pure virtual member.
        /*! This is the method that is called, when we press the "next" button
        */
        virtual bool            next()=0;

    signals:
        void                    lockControls(bool bLock,QList<QWidget*>& lWidgets);/**< signal to lock/unlock a list of controls */
        void                    forward(const QString str);/**< signal to go forward in the tab navigation */
        void                    navigate(const bool bNext, const int idx);/**< signal to navigate in tab */
        void                    hideFrameDetails(bool bNotSubmitted);/**< signal to hide the frame details form */
        void                    showFrameDetails(const FrmFrameDetails::Mode mode,
                                    const FrmFrameDetails::Persistence persistence, Sample* sample, 
                                    QList<int>& blackList=QList<int>(), const int options=FrmFrameDetails::ALLOW_NEW);/**< signal to show the frame details form */
        void                    hideFrmSampling(bool bNotSubmitted);/**< signal to hide the frame details form */
        void                    showFrmSampling();
        void                    showStatus(QString str);//!< signal for showing messages in the status bar
        void                    showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
        void                    currentHelpId(const QString strHelpId);/**< signal for announcing the current help id, set during the focusin event of some UI control*/

        //Signals related to the RuleBinder
        void                     addRecord();/**< tells the rulebinder that an empty record has been initialized*/
        void                     submit();/**< tells the rulebinder that we want to submit a record to the database*/

    protected:
        //! A pure virtual function
        /*! This is an interface function before we actually apply the changes; it is called by the onPreSubmit,
        if everything went ok with the validation;
          \sa onPreSubmit(const bool bSubmit)
        */
        virtual bool            IReallyApply()=0;
        //! A pure virtual function
        /*! Method where we initialize the models (called in the constructor).
        If we want to initialize a model outside the constructor (for instance, each time we show a form),
        don't put it here!
          \sa initMappers(), initUI()
        */
        virtual void            initModels()=0;
        //! A pure virtual function
        /*! Method where we initialize the mappers (called in the constructor).
        If we want to initialize a mapper outside the constructor (for instance, each time we show a form),
        don't put it here!
          \sa initModels(), initUI()
        */
        virtual void            initMappers()=0;
        //! A pure virtual function
        /*! Method where we initialize the user interface (called in the constructor).
        If we want to initialize the UI outside the constructor (for instance, each time we create a record),
        don't put the code here!
          \sa initModels(), initMappers()
      */
        virtual void            initUI()=0;
        //! Init Help Ids
        /*! Abstract function that initializes the m_widgetInfo container, by associating
        widgets and help references.
        */
        virtual void            initHelpIds()=0; 
        //! Get Date Id
        /*! This is an utility function to ge the id of a record on the dateTime Model, provided a QModelIndex;
        It is provided for convenience, to use with the DateTimeCustomCtrl;
          \par mapIdx model row for the record, as integer;
          \par id address of a variable to put the id of the record;
          \sa resizeToVisibleColumns ( QTableView* table )
      */
        bool                    getDtId(const int mapIdx, int& id);
        //! Init Rule Binder
        /*! This function initializes the rule binder, connecting all the necessary signals
        to have interaction with this class;
        the contents of the visible columns.
          \par mapperBinderPtr pointer to a MapperRuleBinder;
      */
        bool                    initBinder(MapperRuleBinder* mapperBinderPtr);

        int                     m_index;/**< tab index */
        const QString           m_title;/**< tab title */
        DateModel*              m_tDateTime;/**< pointer to the DateTime Table, hosted on the main form */
        Sample*                 m_sample;/**< pointer to the Sample structure, hosted on the main form */
        RoleDef*                m_roleDef;/**< pointer to the RoleDef structure, hosted on the login form */
        NullRelationalDelegate* nullDellegate;/**< delegate for handling the null values in AdvancedTextEdit ctrls */
        QLabel*                 lbHead;/**< pointer to the text label on top of the form, indicating if it is logbook or sampling */
        RuleChecker*            m_ruleCheckerPtr;/**< pointer to the rule checker (dynamic business logic layer) */
        MapperRuleBinder*       m_mapperBinderPtr;/**< pointer to the QDataWidgetMapper binder (dynamic business logic layer) */

        QMap<QWidget*, QString> m_widgetInfo;/**< map container to store the widgets and their help ids */
        //! Event Filter
        /*! Reimplemented from QWidget base class.
         \par object sender object
         \par event triggered event
          \sa installEventFilters(), installFilter(QWidget* widget)
        */
        bool                    eventFilter(QObject* object, QEvent* event);
        //! Install Event Filters
        /*! Function that loops through all the UI children and installs the event filters,
        so that we can emit signals during the focusIn event (call in the constructor through initHelpIds()).
          \sa eventFilter(QObject* object, QEvent* event), installFilter(QWidget* widget)
        */
        void                    installEventFilters();
        //! Install Filter
        /*! Recursive part of installEventFilters().
         \par widget widget where we want to install the event filter
          \sa eventFilter(QObject* object, QEvent* event), installEventFilters
        */
        void                    installFilter(QWidget* widget);

    private slots:
        //! Go back
        /*! Slot to navigate back one index, in the tab widget.
          \sa goForward();
        */
        void                    goBack();
        //! Go Forward
        /*! Slot to navigate forward one index, in the tab widget.
          \sa goBack();
        */
        void                    goForward();
        //! On lock controls
        /*! Utility slot where we block/unblock a list of widgets;
          \par bLock boolean to indicate if we want to lock or unlock the controls
          \par lWidgets memory address of a lost of widgets
        */
        void                    onLockControls(bool bLock,QList<QWidget*>& lWidgets);
        //! On pre submit
        /*! This is the slot we call, after the validation process from the binder is over
        (signaled by MapperRuleBinder::finishedPreSubmit());
          \par bSubmit boolean to indicate if the submission process went wrong; if everything went ok,
          we can apply the changes.
          \sa reallyApply(),MapperRuleBinder::finishedPreSubmit()
        */
        void                    onPreSubmit(const bool bSubmit);

};

Q_DECLARE_METATYPE( QList<QWidget*>);
Q_DECLARE_METATYPE( Sample*);

#endif //GENERICTAB_H

//////////////////////////////////////////////////////////////////////
#ifndef SECONDARYFRM_H
#define SECONDARYFRM_H

//! Secondary Frm
/*!
This is a base class for all the forms, that are *not* tabs;
we call them "secondary forms", as opposal to the main form, and they are generally modules.
The need of this class basically arise from the signals that communicate with the main 
class, to send messages (status and error strings)
*/

class SecondaryFrm : public QWidget
{
    Q_OBJECT

    public:
        SecondaryFrm(QWidget *parent = 0, Qt::WFlags flags = 0);

    signals:
        void        hideFrm();
        void        showStatus(QString str);
        void        showError(QString str, const bool bShowMsgBox=true);

};

#endif //SECONDARYFRM_H
//////////////////////////////////////////////////////////////////////
