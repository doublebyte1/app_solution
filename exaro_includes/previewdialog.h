/***************************************************************************
 *   This file is part of the eXaro project                                *
 *   Copyright (C) 2008 by BogDan Vatra                                    *
 *   bog_dan_ro@yahoo.com                                                  *
 **                   GNU General Public License Usage                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 *                                                                         *
 **                  GNU Lesser General Public License                    **
 *                                                                         *
 *   This library is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Lesser General Public License as        * 
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *   You should have received a copy of the GNU Lesser General Public      *
 *   License along with this library.                                      * 
 *   If not, see <http://www.gnu.org/licenses/>.                           *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 ****************************************************************************/

#ifndef REPORTPREVIEWDIALOG_H
#define REPORTPREVIEWDIALOG_H

#include <QDialog>
#include <QIODevice>
#include <QGraphicsPixmapItem>
#include <QSpinBox>

#include "exportinterface.h"

class QSplashScreen;

namespace Report
{


class Document;
class Page;
class PreviewWidget;
class SearchWidget;
class PageGraphicsItem;

class PreviewDialog : public QDialog
{
	Q_OBJECT

public:
	PreviewDialog(QWidget *parent = 0);
	~PreviewDialog();
	void setExportDocument(QDomNode m_exportNode);
	void setDocument(QIODevice * docNode);
	void setVisible(bool visible);
	void setSpaceBetweenPages(int spaceBetweenPages=50);
	void setPrinterName(const QString & name);
	void setShowPrintDialog(bool show);
	void setShowExitConfirm(bool show);
	void setReportName(const QString & name);

protected:
	void reject();
	void drawSelection(QGraphicsItem * parent, QRectF & rect);

public slots:
	void clearSelection();
	void print();
	void firstPage();
	void lastPage();
	void readPrevious();
	void readNext();
	void searchNext(const QString&);
	void searchPrevious(const QString&);
	void exportDocument();

signals:
	void textNotFound();

private:
	QSpinBox * m_zoomSpinBox;
	QDomNode m_exportNode;
	QIODevice * m_docDevice;
	PreviewWidget * m_previewWidget;
	SearchWidget * m_searchWidget;

	Document * m_doc;
	Page * m_searchPage;
	struct pageStruct
	{
		Page * page;
		QGraphicsItem * previewItem;
	};
	QList <pageStruct> m_pages;
	QList<ExportInterface*> m_exports;
	int m_spaceBetweenPages;
	QString m_printerName;
	bool m_showPrintDialog;
	bool m_showExitConfirm;
	QString m_reportName;
};

}

#endif
