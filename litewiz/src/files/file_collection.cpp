/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QList>
#include <QString>
#include <QStringList>
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
void FileCollection::addFiles
(
    QStringList const & fileNames
)
{
    foreach ( QString fileName, fileNames )
    {
        files.append( File( fileName ) );
    }
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
            files.append( File( info ) );
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
QStringList FileCollection::getNames
(
    void
)
{
    QStringList result;

    foreach ( File const & file, files )
    {
        result.append( file.getName() );
    }

    return result;
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

/******************************************************************************/
