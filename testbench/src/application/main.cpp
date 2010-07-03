/*******************************************************************************
*******************************************************************************/

#include <QtCore/QCoreApplication>
#include <QStringList>
#include <stdio.h>
#include "test_bench.h"
#include "console.h"

/*******************************************************************************
*******************************************************************************/
int main
(
    int     argc,
    char ** argv
)
{
    QCoreApplication   application( argc, argv );
    Console            console;
    TestBench          bench( &application );

    bench.run( application.arguments().at( 1 ) );

    return application.exec();
}

/******************************************************************************/
