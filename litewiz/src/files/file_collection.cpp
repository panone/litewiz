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
        File file( fileName );

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
            File file( info );

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

/*******************************************************************************
*******************************************************************************/
File & FileCollection::operator[]
(
    int const index
)
{
    return files[ index ];
}

/*******************************************************************************
*******************************************************************************/
bool FileCollection::exists
(
    File const & file
)
{
    bool result = false;

    foreach ( File const & f, files )
    {
        if( f == file )
        {
            result = true;
            break;
        }
    }

    return result;
}

/******************************************************************************/
