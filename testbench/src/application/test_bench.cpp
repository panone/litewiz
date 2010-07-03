/*******************************************************************************
*******************************************************************************/

#include <QTextStream>
#include "console.h"
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
void TestBench::run
(
    QString const & fileName
)
{
    Classifier classifier;

    Console::output() << QString( "Test set file: %1" ).arg( fileName ) << endl;
    Console::output() << QString( "Result: %1" ).arg( classifier.classify() ) << endl;

    Console::input().readLine();

    emit finished();
}

/******************************************************************************/
