/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QDomDocument>
#include <QDomElement>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include "file.h"
#include "file_collection.h"
#include "item.h"
#include "item_collection.h"
#include "variant.h"
#include "variant_collection.h"
#include "session.h"
#include "aet_session.h"

/*******************************************************************************
*******************************************************************************/
AetSession::AetSession
(
    Session * const session
) :
    session( session )
{
    document       = new QDomDocument();
    title          = "Session";
    rangeSelection = false;
}

/*******************************************************************************
*******************************************************************************/
AetSession::~AetSession
(
    void
)
{
    delete document;
}

/*******************************************************************************
*******************************************************************************/
void AetSession::setTitle
(
    QString const & title
)
{
    if ( !title.isEmpty() )
    {
        this->title = title;
    }
}

/*******************************************************************************
*******************************************************************************/
void AetSession::setAudioDevice
(
    QString const & deviceName
)
{
    if ( !deviceName.isEmpty() )
    {
        audioDevice = deviceName;
    }
}

/*******************************************************************************
*******************************************************************************/
void AetSession::setRangeSelection
(
    bool const selection
)
{
    rangeSelection = selection;
}

/*******************************************************************************
*******************************************************************************/
bool AetSession::save
(
    QString const & fileName
)
{
    QFile file( fileName );

    bool result = file.open( QIODevice::WriteOnly | QIODevice::Text );

    if ( result )
    {
        document->clear();
        document->appendChild( document->createProcessingInstruction( "xml", "version=\"1.0\" encoding=\"utf-8\" " ) );
        document->appendChild( document->createElement( "Session" ) );

        QFileInfo fileInfo( file.fileName() );

        formatSession( document->lastChildElement(), fileInfo.canonicalPath() );

        QTextStream output( &file );

        output << document->toString();

        file.close();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatSession
(
    QDomElement         parent,
    QString     const & sessionPath
)
{
    parent.appendChild( createStringElement( "Title", title ) );

    if ( !audioDevice.isEmpty() )
    {
        parent.appendChild( createStringElement( "AudioDevice", audioDevice ) );
    }

    if ( rangeSelection )
    {
        parent.appendChild( createIntegerElement( "RangeSelection", 1 ) );
    }

    formatVariants( parent );
    formatItems( parent, sessionPath );
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatVariants
(
    QDomElement parent
)
{
    VariantCollection const * variants  = session->getVariants();
    int                       reference = 0;
    QStringList               names;

    for ( int i = 0; i < variants->getCount(); i++ )
    {
        if ( variants->getVariant( i )->isReference() )
        {
            reference = i;
            break;
        }
    }

    Variant const * variant = variants->getVariant( reference );

    if ( !variant->isExcluded() )
    {
        names.append( variant->getName() );
    }

    for ( int i = 0; i < variants->getCount(); i++ )
    {
        variant = variants->getVariant( i );

        if ( ( i != reference ) && !variant->isExcluded() )
        {
            names.append( variants->getVariant( i )->getName() );
        }
    }

    parent.appendChild( createStringListElement( "Variants", names ) );
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatItems
(
    QDomElement         parent,
    QString     const & sessionPath
)
{
    ItemCollection const * items  = session->getItems();

    QDomElement tracks = document->createElement( "Tracks" );

    tracks.setAttribute( "type", "list" );
    tracks.setAttribute( "depth", "1" );
    tracks.setAttribute( "itemtype", "section" );

    for ( int i = 0; i < items->getCount(); i++ )
    {
        if ( !items->getItem( i )->isExcluded() )
        {
            QDomElement item = document->createElement( "Item" );

            formatItem( item, items->getItem( i ), sessionPath );

            tracks.appendChild( item );
        }
    }

    parent.appendChild( tracks );
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatItem
(
    QDomElement               parent,
    Item        const * const item,
    QString     const &       sessionPath
)
{
    FileList    files = session->getFiles()->getItemFiles( item, true, true );
    QDir        sessionDirectory( sessionPath );
    QStringList names;

    foreach ( File const * file, files )
    {
        names.append( sessionDirectory.relativeFilePath( file->getPathName() ) );
    }

    parent.appendChild( createStringElement( "Title", item->getName() ) );
    parent.appendChild( createStringListElement( "Files", names ) );
}

/*******************************************************************************
*******************************************************************************/
QDomElement AetSession::createIntegerElement
(
    QString const &       name,
    int             const value
)
{
    QDomElement result = document->createElement( name );

    result.setAttribute( "type", "integer" );
    result.setAttribute( "value", value );

    return result;
}

/*******************************************************************************
*******************************************************************************/
QDomElement AetSession::createStringElement
(
    QString const & name,
    QString const & value
)
{
    QDomElement result = document->createElement( name );

    result.setAttribute( "type", "string" );
    result.setAttribute( "value", value );

    return result;
}

/*******************************************************************************
*******************************************************************************/
QDomElement AetSession::createStringListElement
(
    QString     const & name,
    QStringList const & values
)
{
    QDomElement result = document->createElement( name );

    result.setAttribute( "type", "list" );
    result.setAttribute( "depth", "1" );
    result.setAttribute( "itemtype", "string" );

    foreach ( QString const & value, values )
    {
        QDomElement item = document->createElement( "Item" );

        item.setAttribute( "value", value );

        result.appendChild( item );
    }

    return result;
}

/******************************************************************************/
