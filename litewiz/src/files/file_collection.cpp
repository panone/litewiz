/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QList>
#include <QString>
#include <QStringList>
#include <QUrl>
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
        addFile( fileName );
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

        directory.setFilter( QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot );

        QFileInfoList fileInfo = directory.entryInfoList();

        foreach ( QFileInfo info, fileInfo )
        {
            if ( info.isDir() )
            {
                addDirectory( info.absoluteFilePath() );
            }
            else
            {
                addFile( info );
            }
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::addUrls
(
    QList< QUrl > const & urls
)
{
    foreach ( QUrl url, urls )
    {
        QFileInfo fileInfo( url.toLocalFile() );

        if ( fileInfo.exists() )
        {
            if ( fileInfo.isDir() )
            {
                addDirectory( fileInfo.absoluteFilePath() );
            }
            else
            {
                addFile( fileInfo );
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
void FileCollection::addFile
(
    QString const & fileName
)
{
    QScopedPointer< File > file( new File( fileName ) );

    if ( !exists( file.data() ) )
    {
        files.append( file.take() );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::addFile
(
    QFileInfo const & fileInfo
)
{
    QScopedPointer< File > file( new File( fileInfo ) );

    if ( !exists( file.data() ) )
    {
        files.append( file.take() );
    }
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
