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

#ifndef REPORTPREVIEWWIDGET_H
#define REPORTPREVIEWWIDGET_H

#include <QGraphicsView>

namespace Report
{


class PreviewWidget : public QGraphicsView
{
	Q_OBJECT
public:
	PreviewWidget(QWidget *parent = 0);
	~PreviewWidget();
	void setZoomStep(qreal step);
	void setZoomMax(qreal max);
	void setZoomMin(qreal min);

public slots:
	void zoomIn();
	void zoomOut();
	void zoomTo(int);

signals:
	void zoomChanged(int);

private:
	qreal m_zoomStep;
	qreal m_zoomMax;
	qreal m_zoomMin;
	qreal m_currentZoom;
};

}

#endif
