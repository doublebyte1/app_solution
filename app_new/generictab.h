#include <QtGui>
#include <QtSql>
#include "frmframedetails.h"
#include "datemodel.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

//////////////////////////////////////////////////////////////////
#ifndef SAMPLE_H
#define SAMPLE_H

//! Sample structure
/*!
This structure encapsulates the data that we want to pass around forms
*/

struct Sample{
    int         frameId;
    int         frameTimeId;
    int         minorStrataId;
    int         cellId;
};

#endif //SAMPLE_H

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
        GenericTab(const int index, Sample* inSample, DateModel* inTDateTime,
            QWidget *parent = 0, Qt::WFlags flags = 0);
        ~GenericTab();

        void                    setLbHead(QLabel* inLbHeader){lbHead=inLbHeader;}

    public slots:
        void                    fillHeader(const QString str){lbHead->setText(str);}
        virtual void            onShowForm()=0;
        virtual bool            next()=0;

    signals:
        void                    lockControls(bool bLock,QList<QWidget*>& lWidgets);
        void                    forward(const QString str);
        void                    gotPar();
        void                    navigate(const bool bNext, const int idx);
        void                    hideFrameDetails(bool bNotSubmitted);
        void                    showFrameDetails(const FrmFrameDetails::Mode mode,
                                    const FrmFrameDetails::Persistence persistence, Sample* sample, 
                                    QList<int>& blackList=QList<int>(), const bool bSupportNewItems=true);
        void                    showStatus(QString str);//!< signal for showing messages in the status bar
        void                    showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages
        void                   submitted(int idx, bool bOk);

    protected:
        virtual void            setHeader()=0;
        virtual void            initModels()=0;
        virtual void            initMappers()=0;
        virtual void            initUI()=0;
        void                    showEvent ( QShowEvent * event );
        bool                    getDtId(const int mapIdx, int& id);
        void                    resizeToVisibleColumns ( QTableView* table );
        int                     m_index;
        DateModel*              m_tDateTime;//pointer to the DateTime Table, hosted on the main form
        Sample*                 m_sample;
        NullRelationalDelegate* nullDellegate;

    private slots:
        void                    goBack();
        void                    goForward();
        void                    onLockControls(bool bLock,QList<QWidget*>& lWidgets);

    private:
        QLabel*                 lbHead;
};

Q_DECLARE_METATYPE( QList<QWidget*>);
Q_DECLARE_METATYPE( Sample*);

#endif //GENERICTAB_H
