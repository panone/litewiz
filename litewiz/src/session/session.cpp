/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QObject>
#include <QStringList>
#include <QTextStream>
#include "file_collection.h"
#include "item_collection.h"
#include "session.h"

/*******************************************************************************
*******************************************************************************/
Session::Session
(
    QObject * parent
) :
    QObject( parent )
{
}

/*******************************************************************************
*******************************************************************************/
void Session::loadFileList
(
    QString const & fileName
)
{
    files.addFiles( getTextFileContents( fileName ) );
}

/*******************************************************************************
*******************************************************************************/
void Session::addFiles
(
    QStringList const & fileNames
)
{
    int count = files.getFileCount();

    files.addFiles( fileNames );

    if ( files.getFileCount() > count )
    {
        emit fileCollectionUpdated();
    }
}

/*******************************************************************************
*******************************************************************************/
void Session::addDirectory
(
    QString const & fileName
)
{
    int count = files.getFileCount();

    files.addDirectory( fileName );

    if ( files.getFileCount() > count )
    {
        emit fileCollectionUpdated();
    }
}

/*******************************************************************************
*******************************************************************************/
FileCollection const & Session::getFiles
(
    void
)
{
    return files;
}

/*******************************************************************************
*******************************************************************************/
void Session::classify
(
    void
)
{
    QStringList fileNames = files.getNames();

    /*
    classifier->classify( fileNames );

    int variance = classifier->getDefaultVariance();

    QList< ItemInfo >      itemInfo    = getItems( variance );
    QList< VariantInfo >   variantInfo = getVariants( variance );

    items.clear();

    foreach ( ItemInfo const & info, itemInfo )
    {
        Item * item = items.addItem( info );

        foreach ( int index, itemInfo.files )
        {
            files.at( index ).setItem( item );
        }
    }

    emit classified();
    */
}

/*******************************************************************************
*******************************************************************************/
QStringList Session::getTextFileContents
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
