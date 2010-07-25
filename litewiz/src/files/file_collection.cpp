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
FileCollection::~FileCollection
(
    void
)
{
    qDeleteAll( files );
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
        File * file = new File( fileName );

        if ( !exists( file ) )
        {
            files.append( file );
        }
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
            File * file = new File( info );

            if ( !exists( file ) )
            {
                files.append( file );
            }
        }
    }
}

/*******************************************************************************
*******************************************************************************/
int FileCollection::getCount
(
    void
)
    const
{
    return files.count();
}

/*******************************************************************************
*******************************************************************************/
File * FileCollection::getFile
(
    int const index
)
    const
{
    return files[ index ];
}

/*******************************************************************************
*******************************************************************************/
FileList FileCollection::getAllFiles
(
    void
)
    const
{
    return files;
}

/*******************************************************************************
*******************************************************************************/
FileList FileCollection::getItemFiles
(
    Item const * const item
)
    const
{
    FileList result;

    foreach ( File * file, files )
    {
        if ( file->getItem() == item )
        {
            result.append( file );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QStringList FileCollection::getNames
(
    void
)
    const
{
    QStringList result;

    foreach ( File const * file, files )
    {
        result.append( file->getName() );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool FileCollection::exists
(
    File const * const file
)
{
    bool result = false;

    foreach ( File const * f, files )
    {
        if ( *f == *file )
        {
            result = true;
            break;
        }
    }

    return result;
}

/******************************************************************************/
