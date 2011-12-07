#include "reportinghook.h"
#include "login.h"
#include <QtGui/QApplication>

#if defined(WIN32) && defined(_DEBUG)
    #define _CRTDBG_MAP_ALLOC
    #include <stdlib.h>
    #include <crtdbg.h>
    #define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__ )
    #define new DEBUG_NEW
#endif

int main(int argc, char *argv[])
{
    #if defined(_MSC_VER) && defined(_DEBUG)
        _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    #endif

    #if defined(WIN32) && defined(_DEBUG)
      setFilterDebugHook();
    #endif

    QApplication a(argc, argv);
    Login l;
    l.show();
    return a.exec();
}
