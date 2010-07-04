/*******************************************************************************
*******************************************************************************/

#include <QDomDocument>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include "classifier.h"
#include "console.h"
#include "test_case.h"
#include "test_bench.h"

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

    if ( !testCases.isEmpty() )
    {
        foreach ( TestCase testCase, testCases )
        {
            testCase.run();
        }
    }

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
            loadTestCases( QFileInfo( file ).canonicalPath(), root );
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
    QString     const & testSetPath,
    QDomElement const & testSet
)
{
    QDomNode node = testSet.firstChild();

    while ( !node.isNull() )
    {
        if ( node.toElement().tagName() == "testCase" )
        {
            TestCase testCase( testSetPath, node.toElement() );

            if ( testCase.isValid() )
            {
                testCases.append( testCase );
            }
        }

        node = node.nextSibling();
    }
}

/******************************************************************************/
