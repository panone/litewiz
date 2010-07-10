/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include "main_window.h"
#include "file_collection.h"

/*******************************************************************************
*******************************************************************************/
int main
(
    int     argc,
    char ** argv
)
{
    QApplication     application( argc, argv );
    MainWindow       mainWindow;
    FileCollection   files;

    files.load( application.arguments().at( 1 ) );

    mainWindow.show();

    return application.exec();
}

/******************************************************************************/
