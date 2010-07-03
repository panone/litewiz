/*******************************************************************************
*******************************************************************************/

#include <QTextStream>
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

    QTextStream consoleOutput( stdout );

    consoleOutput << QString( "Test set file: %1" ).arg( fileName ) << endl;
    consoleOutput << QString( "Result: %1" ).arg( classifier.classify() ) << endl;

    QTextStream consoleInput( stdin );

    consoleInput.readLine();

    emit finished();
}

/******************************************************************************/
