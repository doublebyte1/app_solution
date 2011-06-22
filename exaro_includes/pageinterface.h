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

#ifndef ABSTRACTPAGE_H
#define ABSTRACTPAGE_H

#include <QGraphicsScene>
#include <QList>
#include <QMenu>

#include "globals.h"
#include "iteminterface.h"

/** \namespace Report */
namespace Report
{

/** \class PageInterface
* \brief Interface for pages
*
* This is the base class for all page(s) object(s).
*/
class KONTAMABIL_EXPORTS PageInterface : public QGraphicsScene
{
	Q_OBJECT

	Q_ENUMS(Orientation)
	Q_ENUMS(PageSize)

	Q_PROPERTY(PageSize pageSize READ pageSize WRITE setPageSize)
	Q_PROPERTY(Orientation orientation READ orientation WRITE setOrientation)
	Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
	Q_PROPERTY(QRectF paperRect READ paperRect WRITE setPaperRect)
	Q_PROPERTY(int magnetArea READ magnetArea WRITE setMagnetArea)
	Q_PROPERTY(bool showGrid READ showGrid WRITE setShowGrid)

public:
	enum Orientation { Portrait, Landscape };

	enum PageSize { A4, B5, Letter, Legal, Executive,
	                A0, A1, A2, A3, A5, A6, A7, A8, A9, B0, B1,
	                B10, B2, B3, B4, B6, B7, B8, B9, C5E, Comm10E,
	                DLE, Folio, Ledger, Tabloid, Custom, NPageSize = Custom
	              };
	enum Magnet
	{
		Left = 1,
		Right = 2,
		Top = 4,
		Bottom = 8,
		Vertical = 16,
		Horizontal = 32
	};
public:
	/**
	 * PageInterface constructor
	 * @param parent
	 */
	PageInterface(QObject *parent = 0);

	/**
	 *
	 * @return
	 */
	virtual PageSize pageSize();
	/**
	 *
	 * @param pageSize
	 */
	virtual void setPageSize(PageSize pageSize);

	/**
	 *
	 * @return
	 */
	QRectF paperRect();
	/**
	 *
	 * @param paperRect
	 */
	void setPaperRect(QRectF paperRect);

	/**
	 *
	 * @return
	 */
	virtual Orientation orientation();
	/**
	 *
	 * @param orientation
	 */
	virtual void setOrientation(Orientation orientation);

	/**
	 *
	 * @return
	 */
	virtual QRectF geometry();
	/**
	 *
	 * @param rect
	 */
	virtual void setGeometry(QRectF rect);

	/**
	 *
	 * @return
	 */
	int magnetArea();
	/**
	 *
	 * @param magnetArea
	 */
	void setMagnetArea(int magnetArea);

	/**
	 *
	 * @param parent
	 * @return
	 */
	virtual QObject * createInstance(QObject * parent) = 0;
	/**
	 *
	 * @param object
	 * @return
	 */
	virtual bool canContain(QObject * object) = 0;

	virtual bool showGrid();
	virtual void setShowGrid(bool showGrid);

	virtual void setContextMenu(QMenu * menu);

public slots:
	virtual void setLeftMagnet(bool magneted);
	virtual void setRightMagnet(bool magneted);
	virtual void setTopMagnet(bool magneted);
	virtual void setBottomMagnet(bool magneted);
	virtual void setHorizontalMagnet(bool magneted);
	virtual void setVerticalMagnet(bool magneted);
	virtual void bandDestroyed(int type, int order);

protected:
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void keyPressEvent(QKeyEvent * keyEvent);
	virtual void keyReleaseEvent(QKeyEvent * keyEvent);

	virtual void updatePageRect();
	virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent * contextMenuEvent);

signals:
	/**
	 * This signal is emitted when the item is selected
	 * @param thisObj item object
	 * @param cursorPos cursor position
	 */
	void itemSelected(QObject * thisObject, QPointF cursorPos);

	/**
	 * This signal is emitted when the item geometry is changed
	 * @param newGeometry new geometry
	 */
	void geometryChanged(QRectF newGeometry);

        void itemMoved(QObject*, QPointF);

private:
	void drawMagnets(ItemInterface* item);
	void drawBorder();

private:
	PageSize m_pageSize;
	Orientation m_orientation;
	QRectF m_geometry, m_paperRect;
	QMenu * m_contextMenu;
	int m_magnets, m_magnetArea;
	QList <QGraphicsItem *> m_gideLines;
	QGraphicsRectItem * m_paperBorder;
	QGraphicsRectItem * m_pageBorder;
	bool m_showGrid;
	QGraphicsItem *movingItem;
	QPointF mouseOldPos;
};
}

Q_DECLARE_INTERFACE(Report::PageInterface, "ro.bigendian.Report.PageInterface/1.0");

#endif
