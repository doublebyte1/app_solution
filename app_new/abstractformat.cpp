#include "abstractformat.h"

AbstractFormat::AbstractFormat(const QString name, const QString extension, const QString description)
    : m_name(name), m_extension(extension), m_description(description)
{

}

AbstractFormat::~AbstractFormat()
{
}

bool AbstractFormat::buildFormatFilter(QString& strFilter, QList<absFormatPtr>& formatList)
{
    strFilter=QObject::tr("");// Reset filter for the return test!

    QList<absFormatPtr>::const_iterator i;
    for (i = formatList.constBegin(); i != formatList
        .constEnd(); ++i){

            strFilter.append(i->get()->getDescription());
            strFilter.append(QObject::tr("(*."));
            strFilter.append(i->get()->getExtension());
            strFilter.append(QObject::tr(");; "));

    }
    if (strFilter.length()<1) return false;
    strFilter.remove(strFilter.length()-1,1);
    return true;
}

AbstractFormat* AbstractFormat::findFormat(const QString& strExtension, QList<absFormatPtr>& formatList)
{
    QList<absFormatPtr>::const_iterator i;
    for (i = formatList.constBegin(); i != formatList
        .constEnd(); ++i){
            if (i->get()->getExtension().compare(strExtension)==0)
                return i->get();
    }

    return 0;// Did not find format!
}
