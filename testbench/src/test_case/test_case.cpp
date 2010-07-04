/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QDomElement>
#include <QFile>
#include <QFileInfo>
#include "classifier.h"
#include "console.h"
#include "test_case.h"

/*******************************************************************************
*******************************************************************************/
TestCase::TestCase
(
    QString     const & testSetPath,
    QDomElement const & definition
)
{
    fileName = definition.attribute( "fileName" );
    items    = definition.attribute( "items" ).toInt();
    variants = definition.attribute( "codecs" ).toInt();

    if ( validate() )
    {
        loadFileNameList( testSetPath );
    }
}

/*******************************************************************************
*******************************************************************************/
bool TestCase::isValid
(
    void
)
{
    return valid;
}

/*******************************************************************************
*******************************************************************************/
bool TestCase::run
(
    void
)
{
    bool result = false;

    if ( valid )
    {
        Classifier classifier( fileNames );

        Console::output() << QString( "Result: %1" ).arg( classifier.classify() ) << endl;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool TestCase::validate
(
    void
)
{
    valid = true;

    if ( fileName.isEmpty() )
    {
        Console::output() << "File name list is not specified" << endl;

        valid = false;
    }

    if ( items < 1 )
    {
        Console::output() << QString( "Invalid number of items: %1" ).arg( items ) << endl;

        valid = false;
    }

    if ( variants < 1 )
    {
        Console::output() << QString( "Invalid number of variants: %1" ).arg( variants ) << endl;

        valid = false;
    }

    return valid;
}

/*******************************************************************************
*******************************************************************************/
void TestCase::loadFileNameList
(
    QString const & testSetPath
)
{
    QString fileName = findFileNameList( testSetPath );

    if ( !fileName.isEmpty() )
    {
        fileNames = getTextFileContents( fileName );

        if ( fileNames.isEmpty() )
        {
            Console::output() << "The file name list is empty" << endl;

            valid = false;
        }
    }
}

/*******************************************************************************
*******************************************************************************/
QString TestCase::findFileNameList
(
    QString const & testSetPath
)
{
    QString     result;
    QFileInfo   fileInfo( fileName );
    bool        found = true;

    if ( !fileInfo.exists() )
    {
        fileInfo.setFile( QDir( testSetPath ), fileName );

        if ( !fileInfo.exists() )
        {
            Console::output() << QString( "File name list \"%1\" is not found" ).arg( fileName ) << endl;

            found = false;
        }
    }

    if ( found )
    {
        result = fileInfo.canonicalFilePath();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QStringList TestCase::getTextFileContents
(
    QString const & fileName
)
{
    QStringList   result;
    QFile         file( fileName );

    if ( file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QTextStream stream( &file );

        while ( !stream.atEnd() )
        {
            QString line = stream.readLine();

            if ( !line.isEmpty() )
            {
                result.append( line );
            }
        }
    }
    else
    {
        Console::output() << QString( "Failed to open \"%1\"" ).arg( fileName ) << endl;
    }

    return result;
}

/******************************************************************************/
