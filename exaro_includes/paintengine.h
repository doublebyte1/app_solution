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

#ifndef REPORTPAINTENGINE_H
#define REPORTPAINTENGINE_H

#include <QPaintEngine>
#include <QDomNode>
#include <QPainterPath>

namespace Report
{

class PaintDevice;;

class PaintEngine : public QPaintEngine
{
private:
	PaintEngine(QIODevice * doc);
	friend class PaintDevice;

public:
	~PaintEngine();

	bool begin(QPaintDevice *pdev);
	bool end();

	inline void updateState(const QPaintEngineState &state);

	inline void drawRects(const QRect *rects, int rectCount);
	inline void drawRects(const QRectF *rects, int rectCount);

	inline void drawLines(const QLine *lines, int lineCount);
	inline void drawLines(const QLineF *lines, int lineCount);

	inline void drawEllipse(const QRectF &r);
	inline void drawEllipse(const QRect &r);

	inline void drawPath(const QPainterPath &path);

	inline void drawPoints(const QPointF *points, int pointCount);
	inline void drawPoints(const QPoint *points, int pointCount);

	inline void drawPolygon(const QPointF *points, int pointCount, PolygonDrawMode mode);
	inline void drawPolygon(const QPoint *points, int pointCount, PolygonDrawMode mode);

	inline void drawPixmap(const QRectF &r, const QPixmap &pm, const QRectF &sr);

	inline void drawTextItem(const QPointF &p, const QTextItem &textItem);

	inline void drawTiledPixmap(const QRectF &r, const QPixmap &pixmap, const QPointF &s);

	inline void drawImage(const QRectF &r, const QImage &pm, const QRectF &sr, Qt::ImageConversionFlags flags = Qt::AutoColor);

	inline QPaintEngine::Type type() const;
	inline void writeRect(const QRectF& rect);
	inline void writePoint(const QPointF& point);
	inline void writeLine(const QLineF& line);
	inline void writeBrush(const QBrush& brush);
	inline void writeImage(const QImage& img);
	inline void writeColor(const QColor& color);
	inline void writeFont(const QFont& font);
	inline void writeString(const QString & string);
	inline void writePen(const QPen& pen);
	inline void writeRegion(const QRegion& reg);
	inline void writePath(const QPainterPath& path);
	inline void writeInt(const int & val );
	inline void writeDouble(const qreal & val );
	inline void writeChar(const char & val );
private:
	QIODevice * m_document;
	QDomNode m_pageNode;
	PaintDevice * m_paintDevice;
};

}

#endif
