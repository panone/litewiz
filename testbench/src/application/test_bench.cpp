/*******************************************************************************
*******************************************************************************/

#include <stdio.h>
#include "test_bench.h"
#include "classifier.h"

/*******************************************************************************
*******************************************************************************/
TestBench::TestBench
(
    QObject * const parent
):
    QObject( parent )
{
    connect( this, SIGNAL( finished() ), parent, SLOT( quit() ), Qt::QueuedConnection );
}

/*******************************************************************************
*******************************************************************************/
void TestBench::run()
{
    Classifier classifier;

    printf( "Hello, %d\n", classifier.classify() );
    getc( stdin );

    emit finished();
}

/******************************************************************************/