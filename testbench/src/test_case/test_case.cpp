/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QDomElement>
#include <QFile>
#include <QFileInfo>
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

    validate( testSetPath );
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
        loadFileNames();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void TestCase::validate
(
    QString const & testSetPath
)
{
    valid = true;

    QFileInfo fileInfo( fileName );

    if ( !fileInfo.exists() )
    {
        fileInfo.setFile( QDir( testSetPath ), fileName );

        if ( !fileInfo.exists() )
        {
            Console::output() << QString( "File names list \"%1\" is not found" ).arg( fileName ) << endl;

            valid = false;
        }
        else
        {
            fileName = fileInfo.canonicalFilePath();
        }
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
}

/*******************************************************************************
*******************************************************************************/
void TestCase::loadFileNames
(
    void
)
{
}

/******************************************************************************/
