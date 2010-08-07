/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QObject>
#include <QStringList>
#include <QTextStream>
#include "classifier.h"
#include "utility.h"
#include "variant.h"
#include "file_collection.h"
#include "item_collection.h"
#include "variant_collection.h"
#include "session.h"

/*******************************************************************************
*******************************************************************************/
Session::Session
(
    QObject * parent
) :
    QObject( parent )
{
    files      = new FileCollection;
    items      = new ItemCollection;
    variants   = new VariantCollection;
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
    delete variants;
    delete items;
    delete files;
}

/*******************************************************************************
*******************************************************************************/
void Session::loadFileList
(
    QString const & fileName
)
{
    files->addFiles( getTextFileContents( fileName ) );

    classify();
}

/*******************************************************************************
*******************************************************************************/
void Session::addFiles
(
    QStringList const & fileNames
)
{
    int count = files->getCount();

    files->addFiles( fileNames );

    if ( files->getCount() > count )
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
    int count = files->getCount();

    files->addDirectory( fileName );

    if ( files->getCount() > count )
    {
        emit fileCollectionUpdated();
    }
}

/*******************************************************************************
*******************************************************************************/
void Session::addUrls
(
    QList< QUrl > const & urls
)
{
    int count = files->getCount();

    files->addUrls( urls );

    if ( files->getCount() > count )
    {
        emit fileCollectionUpdated();
    }
}

/*******************************************************************************
*******************************************************************************/
FileCollection * Session::getFiles
(
    void
)
{
    return files;
}

/*******************************************************************************
*******************************************************************************/
ItemCollection * Session::getItems
(
    void
)
{
    return items;
}

/*******************************************************************************
*******************************************************************************/
VariantCollection * Session::getVariants
(
    void
)
{
    return variants;
}

/*******************************************************************************
*******************************************************************************/
void Session::classify
(
    void
)
{
    QStringList fileNames = files->getNames();

    classifier->classify( fileNames );

    setItems( classifier->getDefaultVariance() );
    setVariants( classifier->getDefaultVariance() );

    emit classified();
}

/*******************************************************************************
*******************************************************************************/
void Session::setItems
(
    int const variance
)
{
    items->clear();

    foreach ( ItemInfo const & info, classifier->getItems( variance ) )
    {
        Item * item = items->addItem( info );

        foreach ( int index, info.files )
        {
            files->getFile( index )->setItem( item );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void Session::setVariants
(
    int const variance
)
{
    variants->clear();

    foreach ( VariantInfo const & info, classifier->getVariants( variance ) )
    {
        Variant * variant = variants->addVariant( info );

        variant->setReference( info.reference );

        foreach ( int index, info.files )
        {
            files->getFile( index )->setVariant( variant );
        }
    }
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
