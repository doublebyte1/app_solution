#ifndef FRMLU_H
#define FRMLU_H

#include <QtSql>
#include <QtGui>
#include "ui_frmLU.h"

#if defined(WIN32) && defined(_DEBUG)
 #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
 #define new DEBUG_NEW
#endif

//! Last Update Form
/*!
TODO: class description
*/

class frmlu : public QDialog, public Ui::frmlu
{
    Q_OBJECT

    public:
        frmlu(QWidget *parent = 0);
        ~frmlu();

    private:
        bool                checkID();
        bool                checkMacAddress();

    private slots:
        void                emitLU();

    signals:
        void                LU(const int val, const QString mac);
};

#endif