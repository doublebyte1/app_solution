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

#ifndef BANDINTERFACE_H
#define BANDINTERFACE_H

#include <QObject>
#include <QGraphicsItem>
#include "iteminterface.h"
#include "globals.h"

/** \namespace Report */
namespace Report
{

class TitleItem;

/** \class BandInterface
* \brief Interface for bands
*
* This is the base class for all bands objects.
*/
class KONTAMABIL_EXPORTS BandInterface : public ItemInterface
{
	Q_OBJECT

	Q_ENUMS(BandType)
	Q_FLAGS(Frames Frame);

	/**
	 * @see BandType
	 * @see bandType()
	 * @see setBandType()
	*/
	Q_PROPERTY(BandType bandType READ bandType WRITE setBandType DESIGNABLE false)
	/**
	 * @see order()
	 * @see setOrder()
	*/
	Q_PROPERTY(int order READ order WRITE setOrder)
	/**
	 * @see indentation()
	 * @see setIndentation()
	*/
	Q_PROPERTY(int indentation READ indentation WRITE setIndentation)
	/**
	 * @see frame()
	 * @see setFrame()
	*/
	Q_PROPERTY(Frames frame READ frame WRITE setFrame)
public:
	/**
	* BandType enum
	*
	* @see bandType()
	* @see setBandType()
	*/
	enum BandType {PageHeader, /**< the band is a PageHeader*/
	               Title, /**< the band is a Title*/
	               DetailContainer, /**< the band is a DetailContainer*/
	               DetailHeader, /**< the band is a DetailHeader*/
	               Detail, /**< the band is a Detail*/
	               DetailFooter, /**< the band is a DetailFooter*/
	               Summary, /**< the band is a Summary*/
	               PageFooter, /**< the band is a PageFooter*/
	               Overlay /**< the band is a Overlay*/
	              };

	/**
	* Frame enum
	*
	* @see frame()
	* @see setFrame()
	*/
	enum Frame {DrawLeft = 1, /**< Draw left frame*/
	            DrawRight = 2, /**< Draw right frame*/
	            DrawTop = 4, /**< Draw top frame*/
	            DrawBottom = 8 /**< Draw bottom frame*/
	           };

	/**
	* TitlePosition enum
	*
	* @see drawTitle()
	*/
	enum TitlePosition {TitleLeft, /**< Draw the title on left side*/
			    TitleRight /**< Draw the title on right side*/
			    };
	Q_DECLARE_FLAGS(Frames, Frame);

public:
	/**
	* BandInterface constructor
	*
	* @param parent QGraphicsItem parent
	* @param parentObject QObject parent
	*/
	BandInterface(QGraphicsItem* parent = 0, QObject * parentObject = 0);

	~BandInterface();

	/**
	* Return the type of the band
	* @return BandInterface::BandType band type
	* @see BandType
	* @see setBandType()
	*/
	virtual BandType bandType();

	/**
	 * Set the band geometry.
	 * @param rect the new geometry. The new geometry will be intersected with the page geometry.
	 */
	void setGeometry(QRectF rect);

	/**
	* Return the current order of the band
	* @return current order
	* @see setOrder()
	*/
	int order();
	/**
	* Set the band order. If you have more bands with the same type you can order them.
	* @param order new order
	* @param refreshOthers if this operation should refresh all bands
	* @see order()
	*/
	void setOrder(int order, bool refreshOthers = true);

	/**
	* Return what frame should draw
	* @return BandInterface::Frames
	* @see setFrame()
	* @see Frame
	*/
	Frames frame();
	/**
	* Set the band frames
	* @param frame
	* @see frame()
	* @see Frame
	*/
	void setFrame(Frames frame);

	/**
	* Returns the space between bands.
	* @return int
	*/
	int indentation();
	/**
	* Set the band indentation. The indentation is the space between bands.
	* @param indentation
	*/
	void setIndentation(int indentation);

	virtual void setHeight(qreal height);

	/**
	 * Return the query name
	 * @return query name
	 */
	QString query();
	/**
	 * Sets the query name
	 * @param query query name
	 */
	void setQuery(const QString & query);

	/**
	 * Return true if the band is reprinted on new page
	 * @return true if the band is reprinted on new page
	 */
	bool reprintOnNewPage();
	/**
	 * Set true if this band shoul be reprinted on new page
	 * @param reprintOnNewPage
	 */
	void setReprintOnNewPage(bool reprintOnNewPage);

	bool resetDetailNumber();
	void setResetDetailNumber(bool resetDetailNumber);

	QString groupField();
	void setGroupField(const QString & groupField);

	QVariant groupFieldValue();
	void setGroupFieldValue(const QVariant & groupFieldValue);

	bool deleting();

	void removeItem();

	bool forceNewPage();
	void setForceNewPage(bool forceNewPage);

	void selectBand();

signals:
	void bandDelete(int, int);

protected:
	/**
	* Set the type of the band. This should set only once in the band constructor.
	* @param bandType
	* @see BandType
	* @see bandType()
	*/
	void setBandType(BandType bandType);

	/**
	* Draw the title 
	* @param title title text
	* @param position title position
	* @param position text flags
	* @see TitlePosition
	*/
	virtual void drawTitle(const QString & title, TitlePosition position, int textFlags);

protected slots:
	/**
	 * This slot is called when parent geometry is changed
	 * @param rect parent geometry
	 * @see setGeometry()
	 */
	void updateGeometry(QRectF rect);
	void bandDestroyed(int type, int order);

private:
	QString m_groupField;
	BandType m_bandType;
	int m_order;
	int m_indentation;
	Frames m_frame;
	QString m_query;
	bool m_reprintOnNewPage, m_deleting, m_resetDetailNumber;
	QVariant m_groupFieldValue;
	bool m_forceNewPage;
	TitleItem * m_titleItem;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(BandInterface::Frames);
}
Q_DECLARE_INTERFACE(Report::BandInterface, "ro.bigendian.ReportDesigner.BandInterface/1.0");

#endif
