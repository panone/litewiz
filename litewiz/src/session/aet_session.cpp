/*******************************************************************************
*******************************************************************************/

#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include <QStringList>
#include "file_collection.h"
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
    document = new QDomDocument();
    title    = "Session";
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
QString AetSession::toString
(
    void
)
{
    document->clear();
    document->appendChild( document->createProcessingInstruction( "xml", "version=\"1.0\" encoding=\"utf-8\" " ) );
    document->appendChild( document->createElement( "Session" ) );

    formatSession( document->lastChildElement() );

    return document->toString();
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatSession
(
    QDomElement parent
)
{
    parent.appendChild( createStringElement( "Title", title ) );

    if ( !audioDevice.isEmpty() )
    {
        parent.appendChild( createStringElement( "AudioDevice", audioDevice ) );
    }

    formatVariants( parent );
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatVariants
(
    QDomElement parent
)
{
    VariantCollection const & variants  = session->getVariants();
    int                       reference = 0;
    QStringList               names;

    for ( int i = 0; i < variants.getCount(); i++ )
    {
        if ( variants.getVariant( i )->isReference() )
        {
            reference = i;
            break;
        }
    }

    Variant const * variant = variants.getVariant( reference );

    if ( !variant->isExcluded() )
    {
        names.append( variant->getName() );
    }

    for ( int i = 0; i < variants.getCount(); i++ )
    {
        variant = variants.getVariant( i );

        if ( ( i != reference ) && !variant->isExcluded() )
        {
            names.append( variants.getVariant( i )->getName() );
        }
    }

    parent.appendChild( createStringListElement( "Variants", names ) );
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