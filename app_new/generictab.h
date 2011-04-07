#include <QtGui>
#include <QtSql>
#include "frmframedetails.h"
#include "datemodel.h"

  #if defined(WIN32) && defined(_DEBUG)
     #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
     #define new DEBUG_NEW
  #endif

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
This class implements a generic tab widget
*/

class GenericTab : public QWidget
{
    Q_OBJECT

    public:
        GenericTab(const int index, DateModel* inTDateTime,
            QWidget *parent = 0, Qt::WFlags flags = 0);
        ~GenericTab();

        void            setLbHead(QLabel* inLbHeader){lbHead=inLbHeader;}

    public slots:
        void            fillHeader(const QString str){lbHead->setText(str);}

    signals:
        void            lockControls(bool bLock,QList<QWidget*>& lWidgets);
        void            forward(const QString str);
        void            navigate(const bool bNext, const int idx);
        void            hideFrameDetails();
        void            showFrameDetails(const FrmFrameDetails::Mode mode,
                            const FrmFrameDetails::Persistence persistence, const int frameId);
        void            showStatus(QString str);//!< signal for showing messages in the status bar
        void            showError(QString str, const bool bShowMsgBox=true);//!< signal for error messages

    protected:
        virtual void    setHeader()=0;
        virtual void    initModels()=0;
        virtual void    initMappers()=0;
        virtual void    initUI()=0;
        int             m_index;
        DateModel*      m_tDateTime;//pointer to the DateTime Table, hosted on the main form

    private slots:
        void            goBack();
        void            goForward();
        void            onLockControls(bool bLock,QList<QWidget*>& lWidgets);

    private:
        QLabel*         lbHead;
};

Q_DECLARE_METATYPE( QList<QWidget*>);

#endif //GENERICTAB_H
