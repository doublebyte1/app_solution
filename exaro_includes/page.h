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

#ifndef REPORTPAGE_H
#define REPORTPAGE_H
#include <QPaintDevice>
#include <QPrinter>
#include <QTransform>
#include <QIODevice>
#include <QBrush>
#include <QImage>
#include <QColor>
#include <QFont>
#include <QPen>

#include "paintdevice.h"

namespace Report
{

class Document;

class Page
{
	struct stringStruct
	{
		QRectF textRect;
		qint64 pos;
	};
public:
	enum SearchDirection {NextResult, PreviousResult };
public:
	~Page();
	void render(QPaintDevice * device, const QRectF & exposeRect);
	void render(QPainter * painter, const QRectF & exposeRect);
	QPrinter::Orientation paperOrientation() const;
	QSize pageSize() const;
	bool search(const QString &text, QRectF &rect, SearchDirection direction = NextResult, bool caseSensitive = false, int rectMargin = 5);

private:
	QTransform m_worldTransform;

	Page(QIODevice *doc, qint64 pos);
	friend class Document;

	inline void drawState(QPainter * p);
	inline void drawRect(QPainter * p);
	inline void drawLine(QPainter * p);
	inline void drawEllipse(QPainter * p);
	inline void drawPath(QPainter * p);
	inline void drawPoint(QPainter * p);
	inline void drawPixmap(QPainter * p);
	inline void drawTextItem(QPainter * p);
	inline void drawTiledPixmap(QPainter * p);
	inline void drawImage(QPainter * p);
	inline qreal readDouble();
	inline int readInt();
	inline QBrush readBrush();
	inline QPointF readPoint();
	inline QImage readImage();
	inline QColor readColor();
	inline QString readString();
	inline QFont readFont();
	inline QPen readPen();
	inline QRegion readRegion();
	inline QRectF readRect();
	inline QPainterPath readPath();

private:
	PaintDevice::PageStruct m_pageStruct;
	QIODevice *m_doc;
	qint64 m_pos;
	qint64 m_toPos;
	QPrinter::PaperSize m_paperSize;
	QPrinter::Orientation m_paperOrientation;
	qint64  m_searchPos;
	QString m_searchText;
	QRectF m_exposeRect;
	bool	m_search;
};

}

#endif
