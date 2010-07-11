/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QList>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include "file.h"
#include "file_collection.h"

/*******************************************************************************
*******************************************************************************/
FileCollection::FileCollection
(
    void
)
{
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::load
(
    QString const & fileName
)
{
    QStringList names = getTextFileContents( fileName );

    foreach ( QString name, names )
    {
        append( name );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::append
(
    QString const & filePath
)
{
    File file( filePath );

    files.append( file );
}

/*******************************************************************************
*******************************************************************************/
int FileCollection::getFileCount
(
    void
)
{
    return files.count();
}

/*******************************************************************************
*******************************************************************************/
File const & FileCollection::getFileAt
(
    int const index
)
{
    return files.at( index );
}

/*******************************************************************************
*******************************************************************************/
QStringList FileCollection::getTextFileContents
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

    return result;
}

/******************************************************************************/
