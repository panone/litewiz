/*******************************************************************************
*******************************************************************************/

#include <QDir>
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
        addFile( name );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::addFile
(
    QString const & fileName
)
{
    File file( fileName );

    files.append( file );
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::addDirectory
(
    QString const & fileName
)
{
    QFileInfo info( fileName );

    if ( info.isDir() )
    {
        QDir directory( info.absoluteFilePath() );

        directory.setFilter( QDir::Files );
        directory.setSorting( QDir::Name | QDir::IgnoreCase );

        QFileInfoList fileInfo = directory.entryInfoList();

        foreach ( QFileInfo info, fileInfo )
        {
            addFile( info.absoluteFilePath() );
        }
    }
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
FileCollection::const_iterator FileCollection::begin
(
    void
)
    const
{
    return files.begin();
}

/*******************************************************************************
*******************************************************************************/
FileCollection::const_iterator FileCollection::end
(
    void
)
    const
{
    return files.end();
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
