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

#ifndef ABSTRACTREPORTITEM_H
#define ABSTRACTREPORTITEM_H
#include <QGraphicsItem>
#include <QObject>
#include <QIcon>
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QScriptEngine>

#include "globals.h"

/** @namespace Report */

namespace Report
{

class SqlQuery;
class ReportInterface;

/** @class ItemInterface
* @brief Interface for items
*
* This is the base class for all items objects.
* The code above show you how to add an rectangle item.
*
* rect.h
* @code
#ifndef RECT_H
#define RECT_H
#include <iteminterface.h>
class Rectangle : public Report::ItemInterface
{
	Q_OBJECT
	Q_INTERFACES(Report::ItemInterface);

public:
	Rectangle(QGraphicsItem* parent = 0, QObject* parentObject = 0);

	QRectF boundingRect() const;
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

	QString toolBoxText();
	QString toolBoxGroup();

	QObject * createInstance(QGraphicsItem* parent = 0, QObject* parentObject = 0);

};
#endif
* @endcode
* rect.cpp
* @code
#include <QtCore>
#include <QBrush>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include "rect.h"
Rectangle::Rectangle(QGraphicsItem* parent, QObject* parentObject) : ItemInterface(parent, parentObject)
{
}

QRectF Rectangle::boundingRect() const
{
	return QRectF(0, 0, width(), height()); // return the boundingRect()
}

void Rectangle::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	Q_UNUSED(widget);
	QRectF rect = (option->type == QStyleOption::SO_GraphicsItem) ? boundingRect() : option->exposedRect;
	if (option->type == QStyleOption::SO_GraphicsItem)
		drawSelection(painter, rect); // if the item is in designer (option->type == QStyleOption::SO_GraphicsItem)

	setupPainter(painter);

	adjustRect(rect);

	painter->drawRect(rect); // draw the rectangle !!
}

QString Rectangle::toolBoxText()
{
	return tr("Rectangle");
}

QString Rectangle::toolBoxGroup()
{
	return tr("Shapes");
}

QObject * Rectangle::createInstance(QGraphicsItem* parent, QObject* parentObject)
{
	return new Rectangle(parent, parentObject);
}

Q_EXPORT_PLUGIN2(rectangle, Rectangle)

* @endcode
* Yes it's that simple !!!
*/

class KONTAMABIL_EXPORTS ItemInterface: public QObject, public QGraphicsItem
{
	Q_OBJECT

	Q_ENUMS(BGMode)

	/**
	 * @see geometry()
	 * @see setGeometry()
	*/
	Q_PROPERTY(QRectF geometry READ geometry WRITE setGeometry)
	/**
	 * @see pen()
	 * @see setPen()
	*/
	Q_PROPERTY(QPen pen READ pen WRITE setPen)
	/**
	 * @see brush()
	 * @see setBrush()
	*/
	Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
	/**
	 * @see backgroundBrush()
	 * @see setBackgroundBrush()
	*/
	Q_PROPERTY(QBrush backgroundBrush READ backgroundBrush WRITE setBackgroundBrush)
	/**
	 * @see backgroundMode()
	 * @see setBackgroundMode()
	 * @see BGMode
	*/
	Q_PROPERTY(BGMode backgroundMode READ backgroundMode WRITE setBackgroundMode)
	/**
	 * @see opacity()
	 * @see setOpacity()
	*/
	Q_PROPERTY(int opacity READ opacity WRITE setOpacity)
	/**
	 * @see font()
	 * @see setFont()
	*/
	Q_PROPERTY(QFont font READ font WRITE setFont)

public:
	/** @enum BGMode
	* @see backgroundMode()
	* @see setBackgroundMode()
	*/
	enum BGMode { TransparentMode, /**< Background is transparent*/
	              OpaqueMode /**< Background is opaque*/
	            };

	/** @enum ResizeFlags
	* @see resizeFlags()
	* @see setResizeFlags()
	*/
	enum ResizeFlags {Fixed = 0, /**< Item cant be resized*/
	                  ResizeLeft = 1, /**< Item can be resized to left*/
	                  ResizeRight = 2, /**< Item can be resized to right*/
	                  ResizeTop = 4, /**< Item can be resized to top*/
	                  ResizeBottom = 8, /**< Item can be resized to bottom*/
	                  FixedPos = 16 /**< Item cant be moved*/
	                 };

public:
	/**
	 * ItemInterface constructor
	 * @param parent parent item
	 * @param parentObject parent object
	 */
	ItemInterface(QGraphicsItem* parent = 0, QObject * parentObject = 0);
	virtual ~ItemInterface();

	/**
	 * Return resizeHandle pixels
	 * @return pixels
	 * @see setResizeHandle()
	 */
	int resizeHandle();
	/**
	 * Set resizeHandle pixels (default 6)
	 * @param resizeHandle pixels
	 * @see resizeHandle()
	 */
	void setResizeHandle(int resizeHandle);

	/**
	 * Return the brush used to paint background
	 * @return backgroundBrush
	 * @see setBackgroundBrush()
	 */
	virtual QBrush backgroundBrush();
	/**
	 * Set the brush used to paint background
	 * @param brush brush used to paint background
	 * @see backgroundBrush()
	 */
	virtual void setBackgroundBrush(const QBrush & brush);

	/**
	 * Return the brush used to paint the item
	 * @return  the brush used to paint the item
	 * @see setBrush()
	 */
	virtual QBrush brush();
	/**
	 * Set the brush used to paint the item
	 * @param brush brush used to paint the item
	 * @see brush()
	 */
	virtual void setBrush(const QBrush & brush);


	/**
	 * Return the pen used to paint the item
	 * @return pen used to paint the item
	 * @see setPen()
	 */
	virtual QPen pen();
	/**
	 * Set the pen used to paint the item
	 * @param pen
	 * @see pen()
	 */
	virtual void setPen(const QPen & pen);


	/**
	 * Return the item font
	 * @return item font
	 * @see setFont()
	 */
	virtual QFont font();
	/**
	 * Set the item font
	 * @param font item font
	 * @see font()
	 */
	virtual void setFont(const QFont & font);

	/**
	 * Return the item width
	 * @return item width
	 * @see setWidth();
	 */
	virtual qreal width() const;
	/**
	 * Set the item width
	 * @param width
	 * @see width();
	 */
	virtual void setWidth(qreal width);

	/**
	 * Return the item height
	 * @return item height
	 * @see setHeight()
	 */
	virtual qreal height() const;
	/**
	 * Set the item height
	 * @param height item height
	 * @see height()
	 */
	virtual void setHeight(qreal height);
	/**
	* Returns the band stretch.
	* @return int
	*/
	qreal stretch();
	/**
	* Set the band stretch.
	* @param val stretch value
	*/
	void setStretch(qreal val);
	/**
	* Set the band stretch to 0.
	*/
	void unstretch();

	/**
	 * Return the item minimal width
	 * @return item min width
	 * @see setMinWidth()
	 */
	virtual qreal minWidth() const;
	/**
	 * Return the item minimal height
	 * @return item min height
	 * @see setMinHeight()
	 */
	virtual qreal minHeight() const;
	/**
	 * Set the item minimum height
	 * @param height item minimum height
	 * @see minHeight()
	 */
	virtual void setMinHeight(qreal height);
	/**
	 * Set the item minimum width
	 * @param width item width
	 * @see minWidth()
	 */
	virtual void setMinWidth(qreal width);
	/**
	 * Return background mode
	 * @return background mode
	 * @see BGMode
	 * @see setBackgroundMode()
	 */
	virtual BGMode backgroundMode();
	/**
	 * Set background mode
	 * @param bgMode background mode
	 * @see BGMode
	 * @see backgroundMode()
	 */
	virtual void setBackgroundMode(BGMode bgMode);

	/**
	 * Return resize flags
	 * @return resize flags
	 * @see ResizeFlags
	 */
	int resizeFlags();

	/**
	 * Return resize flags for a given point
	 * @param cursor cursor point
	 * @return resize flags
	 */
	int posibleResizeCurrsor(QPointF cursor);

	/**
	 * Return the item geometry
	 * @return item geometry
	 */
	virtual QRectF geometry();
	/**
	 * Set the item geometry
	 * @param rect item geometry
	 */
	virtual void setGeometry(QRectF rect);

	/**
	 * Return the icon for tool box
	 * @return icon
	 */
	virtual QIcon toolBoxIcon()
	{
		return QIcon();
	};

	/**
	 * Return the item name for tool box
	 * @return item name
	 */
	virtual QString toolBoxText() = 0;
	/**
	 * Return the item group
	 * @return item group
	 */
	virtual QString toolBoxGroup() = 0;

	/**
	 * This function defines the outer bounds of the item as a rectangle; all painting must be restricted to inside an item's bounding rect.
	 * @return bounding rect
	 */
	QRectF boundingRect() const
	{
		return QRectF();
	};

	/**
	 * This function prepare the item. Only in this function you can resize or stretch your item
	 * @param painter the painter used to paint in
	 */
	virtual void prepare(QPainter * painter);

	/**
	 * This function. This function is called before paint function. The default implementation will emmit beforePrint signal. 
	 * if you reimplement this method don't forget to emmit beforePrint signal or to call parents method
	 * @param painter the painter used to paint in
	 */
	virtual void beginPaint(QPainter * painter);

	/**
	 * This function paints the contents of an item
	 * @param painter the painter used to paint in
	 * @param option provides style options for the item, such as its state, exposed area and its level-of-detail hints.
	 * @param widget the widget argument is optional. If provided, it points to the widget that is being painted on; otherwise, it is 0. For cached painting, widget is always 0.
	 */
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

	/**
	 * This function. This function is called after paint function. The default implementation will emmit afterPrint signal.
	 * if you reimplement this method don't forget to emmit this afterPrint or to call parents method
	 * @param painter the painter used to paint in
	 */
	virtual void endPaint(QPainter * painter);

	/**
	 * This pure virtual function is used to create the item object
	 * @param parent parent item
	 * @param parentObj parent object
	 * @return item instance
	 */
	virtual QObject * createInstance(QGraphicsItem* parent = 0, QObject * parentObj = 0) = 0;

	/**
	 * Before you add a object to this item, call this method to see if this item can containt the object.
	 * @param object object you want to add
	 * @return true if the report can contain the object
	 */
	virtual bool canContain(QObject * object);

	/**
	 * Adjust the rect with pen width
	 * @param rect rect to adjust
	 * @return adjusted rect
	 */
	QRectF adjustRect(QRectF & rect);

	/**
	 * Try to find the report query query
	 * @param query query to search
	 * @return a valid SqlQuery query pointer or 0.
	 */
	SqlQuery * findQuery(const QString & query);

	/**
	 * Return the field from query
	 * @param query query to find
	 * @param field field to find
	 * @return an QVariant value or an error message
	 */
	QVariant queryField(const QString & query, const QString & field);

	/**
	 * Return the report script engine
	 * @return script engine
	 */
	QScriptEngine * scriptEngine();

	/**
	 * Returns the report object of the item
	 * @return report object
	 */
	ReportInterface	* reportObject();

	/**
	* Return the item opacity
	* @return item opacity
	* @see setOpacity()
	*/
	virtual int opacity();
	/**
	 * Set the item opacity
	 * @param opacity item opacity
	 * @see opacity()
	 */
	virtual void setOpacity(const int opacity);

	/**
	 * Return the parent geometry
	 * @return parent geometry
	 */
	QRectF parentGeometry();

	virtual void removeItem(){/*deleteLater();*/};

protected:
	/**
	 * This event handler, for event event, can be reimplemented to receive mouse press events for this item. Mouse press events are only delivered to items that accept the mouse button that is pressed. By default, an item accepts all mouse buttons, but you can change this by calling setAcceptedMouseButtons().
	 * @param event QGraphicsSceneMouseEvent
	 */
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	/**
	 * This event handler, for event event, can be reimplemented to receive mouse release events for this item.
	 * @param event QGraphicsSceneMouseEvent
	 */
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	/**
	 * This event handler, for event event, can be reimplemented to receive mouse move events for this item. If you do receive this event, you can be certain that this item also received a mouse press event, and that this item is the current mouse grabber.
	 * @param event QGraphicsSceneMouseEvent
	 */
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

	/**
	 * Set the resizeFlags for the item. This should set only once in the item constructor.
	 * @param resizeFlags
	 * @see ResizeFlags
	 */
	void setResizeFlags(int resizeFlags);

	/**
	 * This function is used to draw the selection of the item
	 * @param painter the painter to draw to
	 * @param rect bounding rect
	 */
	void drawSelection(QPainter * painter, QRectF rect);

	/**
	 * This function set the background brush, the brush, the pen and the font to painter
	 * @param painter
	 */
	void setupPainter(QPainter * painter);

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

	/**
	 * This signal should be emitted before printing
	 * @param sender object how emitt the signal
	 */
	void beforePrint(QObject * sender);

	/**
	 * This signal should be emitted after printing
	 * @param sender object how emitt the signal
	 */
	void afterPrint(QObject * sender);
	
	void geometryChanged(QObject * object, QRectF newGeometry, QRectF oldGeometry);

private:
	int m_resizeHandle;
	int m_resizeEvent;
	BGMode m_BGMode;
	int m_resizeFlags;
	qreal m_width, m_height;
 	qreal m_minWidth, m_minHeight;
	QBrush m_brush, m_backgroundBrush;
	QPen m_pen;
	QFont m_font;
	int m_opacity;
	qreal m_stretch;
	QRectF oldGeometry;
	bool m_drawSelectionBorder;
};
}

Q_DECLARE_INTERFACE(Report::ItemInterface, "ro.bigendian.Report.ItemInterface/1.0");
#endif
