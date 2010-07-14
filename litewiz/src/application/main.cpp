/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include "main_window.h"

/*******************************************************************************
*******************************************************************************/
int main
(
    int     argc,
    char ** argv
)
{
    QApplication application( argc, argv );

    QApplication::setOrganizationName( "Litewiz Productions" );
    QApplication::setApplicationName( "Litewiz" );

    MainWindow mainWindow;

    mainWindow.show();

    return application.exec();
}

/******************************************************************************/
