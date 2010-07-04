/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QDomDocument>
#include <QTextStream>
#include "console.h"
#include "test_bench.h"
#include "classifier.h"

/*******************************************************************************
*******************************************************************************/
TestBench::TestBench
(
    QObject * const parent
) :
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
    loadTestSet( fileName );

    Classifier classifier;

    Console::output() << QString( "Test set file: %1" ).arg( fileName ) << endl;
    Console::output() << QString( "Result: %1" ).arg( classifier.classify() ) << endl;

    Console::input().readLine();

    emit finished();
}

/*******************************************************************************
*******************************************************************************/
void TestBench::loadTestSet
(
    QString const & fileName
)
{
    QFile          file( fileName );
    QDomDocument   doc;
    QString        errorMessage;
    int            errorLine;
    int            errorColumn;

    if ( doc.setContent( &file, &errorMessage, &errorLine, &errorColumn ) )
    {
        QDomElement root = doc.documentElement();

        if ( root.tagName() == "testSet" )
        {
            loadTestCases( root );
        }
    }
    else
    {
        Console::output() << QString( "Parsing error: %1 (%2, %3)" ).arg( errorMessage ).arg( errorLine ).arg( errorColumn ) << endl;
    }
}

/*******************************************************************************
*******************************************************************************/
void TestBench::loadTestCases
(
    QDomElement const & testSet
)
{
    QDomNode node = testSet.firstChild();

    while ( !node.isNull() )
    {
        if ( node.toElement().tagName() == "testCase" )
        {
            //loadTestCase();
        }

        node = node.nextSibling();
    }
}

/******************************************************************************/
