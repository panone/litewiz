/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QList>
#include <QString>
#include <QStringList>
#include <QUrl>
#include "variant.h"
#include "file.h"
#include "file_collection.h"

/*******************************************************************************
*******************************************************************************/
bool FileCollection::variantIndexCompare
(
    File const * const file1,
    File const * const file2
)
{
    return file1->getVariant()->getIndex() < file2->getVariant()->getIndex();
}

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
void FileCollection::removeFile
(
    QString const & fileName
)
{
    foreach ( File * file, files )
    {
        if ( file->getPathName() == fileName )
        {
            files.removeOne( file );

            delete file;

            break;
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void FileCollection::removeDirectory
(
    QString const & fileName
)
{
    foreach ( File * file, files )
    {
        if ( file->getPath() == fileName )
        {
            files.removeOne( file );

            delete file;
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
    Item const * const item,
    bool         const skipExcluded,
    bool         const referenceFirst
)
    const
{
    FileList result;

    foreach ( File * file, files )
    {
        if ( ( file->getItem() == item ) && !( skipExcluded && file->isExcluded() ) )
        {
            result.append( file );
        }
    }

    qSort( result.begin(), result.end(), FileCollection::variantIndexCompare );

    if ( referenceFirst )
    {
        int refenence = 0;

        for ( int i = 0; i < result.count(); i++ )
        {
            if ( result.value( i )->getVariant()->isReference() )
            {
                refenence = i;
            }
        }

        if ( refenence != 0 )
        {
            result.move( refenence, 0 );
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
