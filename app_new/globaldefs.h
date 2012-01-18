#include <QDir>

#ifndef GLOBALDEFS_H
#define GLOBALDEFS_H

//! Global Defs
/*!
This is just a file where we store all the string constants, in a translating friendly way,
so that we are able to change them easily on a global basis.
*/

static const char *strNa = 
     QT_TRANSLATE_NOOP("null_replacements", "n/a");

static const char *strMissing = 
     QT_TRANSLATE_NOOP("null_replacements", "missing");

static const char *strOther = 
     QT_TRANSLATE_NOOP("null_replacements", "other");

static const char *strUnknown = 
     QT_TRANSLATE_NOOP("null_replacements", "unknown");

static const char *strOutside = 
     QT_TRANSLATE_NOOP("bin", "outside");

static const char *strBin = 
     QT_TRANSLATE_NOOP("bin", "bin");

static const char *strDragged = 
     QT_TRANSLATE_NOOP("dragged", "Dragged by parent");

static const char *strRoot = 
     QT_TRANSLATE_NOOP("frame", "root");

static const char *strLogbook = 
     QT_TRANSLATE_NOOP("frame", "logbook");

static const char *strSampling = 
     QT_TRANSLATE_NOOP("frame", "Artisanal Fisheries");
     //QT_TRANSLATE_NOOP("frame", "Sampling");

static const QString strReportsDir = 
    QDir::currentPath() + QDir::separator() + "reports";

static const char *strEmpty = 
     QT_TRANSLATE_NOOP("empty", "empty");

static const QString strDatabaseDriver = 
     "SQL SERVER";

#endif// GLOBALDEFS_H