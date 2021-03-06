/*******************************************************************************
*******************************************************************************/

#include <QFile>
#include <QObject>
#include <QSet>
#include <QSettings>
#include <QStringList>
#include <QTextStream>
#include "classifier.h"
#include "utility.h"
#include "variant.h"
#include "file_collection.h"
#include "item_collection.h"
#include "variant_collection.h"
#include "file_tree_item.h"
#include "session.h"

/*******************************************************************************
*******************************************************************************/
DEFINE_CONST_RUNNABLE_2( AddFiles, FileCollection *, files, QStringList const &, fileNames )
{
    files->addFiles( fileNames );
}

/*******************************************************************************
*******************************************************************************/
DEFINE_CONST_RUNNABLE_2( AddDirectory, FileCollection *, files, QString const &, fileName )
{
    files->addDirectory( fileName );
}

/*******************************************************************************
*******************************************************************************/
DEFINE_CONST_RUNNABLE_2( AddUrls, FileCollection *, files, QList< QUrl > const &, urls )
{
    files->addUrls( urls );
}

/*******************************************************************************
*******************************************************************************/
DEFINE_CONST_RUNNABLE_2( RemoveFiles, FileCollection *, files, QSet< FileTreeItem * > const &, items )
{
    foreach ( FileTreeItem * item, items )
    {
        if ( item->isDirectory() )
        {
            files->removeDirectory( item->getPathName() );
        }
        else
        {
            files->removeFile( item->getPathName() );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
Session::Session
(
    QObject * parent
) :
    QObject( parent )
{
    autoClassify = true;
    classified   = false;

    files      = new FileCollection;
    items      = new ItemCollection;
    variants   = new VariantCollection;
    classifier = new Classifier;

    loadSettings();
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
    addFiles( getTextFileContents( fileName ) );
}

/*******************************************************************************
*******************************************************************************/
void Session::addFiles
(
    QStringList const & fileNames
)
{
    updateFileCollection( AddFiles( files, fileNames ) );
}

/*******************************************************************************
*******************************************************************************/
void Session::addDirectory
(
    QString const & fileName
)
{
    updateFileCollection( AddDirectory( files, fileName ) );
}

/*******************************************************************************
*******************************************************************************/
void Session::addUrls
(
    QList< QUrl > const & urls
)
{
    updateFileCollection( AddUrls( files, urls ) );
}

/*******************************************************************************
*******************************************************************************/
void Session::removeFiles
(
    QSet< FileTreeItem * > const & items
)
{
    updateFileCollection( RemoveFiles( files, items ) );
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
QIntList Session::getPossibleVariance
(
    void
)
{
    return variance;
}

/*******************************************************************************
*******************************************************************************/
int Session::getCurrentVariance
(
    void
)
{
    return variants->getCount();
}

/*******************************************************************************
*******************************************************************************/
void Session::applySettings
(
    void
)
{
    if ( files->getCount() > 0 )
    {
        if ( autoClassify && !classified )
        {
            classify();
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void Session::updateFileCollection
(
    ConstRunnable const & update
)
{
    int count = files->getCount();

    update.run();

    if ( files->getCount() != count )
    {
        if ( autoClassify )
        {
            classify();
        }
        else
        {
            invalidateClassification();
        }

        emit fileCollectionUpdated();
    }
}

/*******************************************************************************
*******************************************************************************/
void Session::setItems
(
    ClassificationInfo const & classification
)
{
    items->clear();

    foreach ( ItemInfo const & info, classification.items )
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
    ClassificationInfo const & classification
)
{
    variants->clear();

    foreach ( VariantInfo const & info, classification.variants )
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
void Session::invalidateClassification
(
    void
)
{
    if ( classified )
    {
        variance.clear();

        classified = false;

        emit classificationChanged();
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

/*******************************************************************************
*******************************************************************************/
void Session::loadSettings
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "Options" );

    autoClassify = settings.value( "AutoClassify", true ).toBool();

    applySettings();
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

    variance = classifier->getPossibleVariance();

    ClassificationInfo classification = classifier->getClassification( classifier->getDefaultVariance() );

    setItems( classification );
    setVariants( classification );

    classified = true;

    emit classificationChanged();
}

/*******************************************************************************
*******************************************************************************/
void Session::setCurrentVariance
(
    int const varianceIndex
)
{
    if ( ( varianceIndex >= 0 ) && ( varianceIndex < variance.count() ) )
    {
        ClassificationInfo classification = classifier->getClassification( variance.value( varianceIndex ) );

        setItems( classification );
        setVariants( classification );

        emit classificationChanged();
    }
}

/******************************************************************************/
