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

#ifndef REPORTREPORTENGINE_H
#define REPORTREPORTENGINE_H

#include <QObject>
#include <QList>
#include <QMap>

#include "reportinterface.h"
#include "pageinterface.h"
#include "iteminterface.h"
#include "bandinterface.h"
#include "globals.h"

namespace Report
{

class KONTAMABIL_EXPORTS ReportEngine : public QObject
{
	Q_OBJECT

public:
	ReportEngine(QObject *parent = 0);

	~ReportEngine();

	/**
	 * Return a map of items (plugins). The key reprezents the section of the item
	 * @return items
	 */
	const QMap<QString, Report::ItemInterface*> & items() const;
	/**
	 * Retrun a list of page plugins.
	 * @return pages
	 */
	const QList<Report::PageInterface*>  & pages() const;
	/**
	 * Return a list o report plugins
	 * @return report
	 */
	const QList<Report::ReportInterface*> & reports() const;

	/**
	 * Save the report
	 * @param fileName
	 * @param report
	 * @return true is success
	 */
	bool saveReport(const QString & fileName, ReportInterface * report);

	/**
	 * Load a report
	 * @param fileName
	 * @return an instance of report or 0.
	 */
	ReportInterface* loadReport(const QString & fileName);

	/**
	 * Load a report
	 * @param device
	 * @return an instance of report or 0.
	 */
	ReportInterface* loadReport(QIODevice * device);

	/**
	 * Load a report
	 * @param content
	 * @return an instance of report or 0.
	 */
	ReportInterface* loadReportFromString(const QString & content);

	static QString uniqueName(const QString &name, QObject * rootObject);
	static bool isUniqueName(QObject * object, QString name);

	static void setObjectPropertiesFromDom(QObject * object, const QDomElement & dom);

	static QDomElement objectProperties(QObject * object, QDomDocument * doc);
	QObject * objectFromDom(QObject * parent, const QDomElement & dom);

	QObject* paste(QObject* parent);
	void copy(QObject* object);

	ItemInterface * findItemByClassName(const QString & name);
private:
	static bool cmpBands(BandInterface * b1, BandInterface * b2);

private:
	QMap<QString, ItemInterface*> m_items;
	QList<PageInterface*> m_pages;
	QList<ReportInterface*> m_reports;
	QString lastObject;
};

}

#endif
