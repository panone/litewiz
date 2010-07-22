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
    document = 0;
    title    = "Session";
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
    document = new QDomDocument();

    QDomElement root = createRootElement();

    formatSession( root );

    QString result = document->toString();

    delete document;

    return result;
}

/*******************************************************************************
*******************************************************************************/
void AetSession::formatSession
(
    QDomElement & parent
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
    QDomElement & parent
)
{
    VariantCollection const & variants = session->getVariants();
    QStringList               names;

    for ( int i = 0; i < variants.getCount(); i++ )
    {
        names.append( variants.getVariant( i )->getName() );
    }

    parent.appendChild( createStringListElement( "Variants", names ) );
}

/*******************************************************************************
*******************************************************************************/
QDomElement AetSession::createRootElement
(
    void
)
{
    QDomElement root = document->createElement( "Session" );

    document->appendChild( root );

    return root;
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

    result.setAttribute( "type", "string" );
    result.setAttribute( "count", values.count() );

    foreach ( QString const & value, values )
    {
        QDomElement item = document->createElement( "Item" );

        item.setAttribute( "value", value );

        result.appendChild( item );
    }

    return result;
}

/******************************************************************************/
