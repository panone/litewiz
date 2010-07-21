/*******************************************************************************
*******************************************************************************/

#include <QDomDocument>
#include <QDomElement>
#include <QString>
#include "file_collection.h"
#include "item_collection.h"
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
QString AetSession::toString
(
    void
)
{
    QDomElement root = createDocument();

    root.appendChild( createStringElement( "Title", title ) );

    QString result = document->toString();

    delete document;

    return result;
}

/*******************************************************************************
*******************************************************************************/
QDomElement AetSession::createDocument
(
    void
)
{
    document = new QDomDocument();

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

/******************************************************************************/
