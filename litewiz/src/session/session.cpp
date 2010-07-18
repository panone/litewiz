/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QObject>
#include <QStringList>
#include <QTextStream>
#include "classifier.h"
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
    classifier = new Classifier;
}

/*******************************************************************************
*******************************************************************************/
Session::~Session
(
    void
)
{
    delete classifier;
}

/*******************************************************************************
*******************************************************************************/
void Session::loadFileList
(
    QString const & fileName
)
{
    files.addFiles( getTextFileContents( fileName ) );

    classify();
}

/*******************************************************************************
*******************************************************************************/
void Session::addFiles
(
    QStringList const & fileNames
)
{
    int count = files.getCount();

    files.addFiles( fileNames );

    if ( files.getCount() > count )
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
    int count = files.getCount();

    files.addDirectory( fileName );

    if ( files.getCount() > count )
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
ItemCollection const & Session::getItems
(
    void
)
{
    return items;
}

/*******************************************************************************
*******************************************************************************/
void Session::classify
(
    void
)
{
    QStringList fileNames = files.getNames();

    classifier->classify( fileNames );

    int variance = classifier->getDefaultVariance();

    QList< ItemInfo >      itemInfo    = classifier->getItems( variance );
    QList< VariantInfo >   variantInfo = classifier->getVariants( variance );

    items.clear();

    foreach ( ItemInfo const & info, itemInfo )
    {
        Item * item = items.addItem( info );

        foreach ( int index, info.files )
        {
            files[ index ].setItem( item );
        }
    }

    emit classified();
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
