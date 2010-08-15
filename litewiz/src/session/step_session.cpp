/*******************************************************************************
*******************************************************************************/

#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>
#include "file.h"
#include "file_collection.h"
#include "item.h"
#include "item_collection.h"
#include "variant.h"
#include "session.h"
#include "step_session.h"

/*******************************************************************************
*******************************************************************************/
StepSession::StepSession
(
    Session * const session
) :
    session( session )
{
    type            = MushraSession;
    hiddenReference = false;
}

/*******************************************************************************
*******************************************************************************/
void StepSession::setType
(
    int const type
)
{
    this->type = type;
}

/*******************************************************************************
*******************************************************************************/
void StepSession::addHiddenReference
(
    bool const add
)
{
    hiddenReference = add;
}

/*******************************************************************************
*******************************************************************************/
bool StepSession::save
(
    QString const & fileName
)
{
    QFile file( fileName );

    bool result = file.open( QIODevice::WriteOnly | QIODevice::Text );

    if ( result )
    {
        QFileInfo     fileInfo( file.fileName() );
        QTextStream   output( &file );

        output << formatSession( fileInfo.canonicalPath() );

        file.close();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QString StepSession::formatSession
(
    QString const & sessionPath
)
{
    QString result = QString( "session=%1\n" ).arg( getType() );

    result += formatItems( sessionPath );

    return result;
}

/*******************************************************************************
*******************************************************************************/
QString StepSession::getType
(
    void
)
{
    QString result;

    switch ( type )
    {
        case AbSession:
            result = "A-B";
            break;

        default:
            result = "mushra";
            break;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QString StepSession::formatItems
(
    QString const & sessionPath
)
{
    ItemCollection const * items = session->getItems();
    QString                result;

    for ( int i = 0; i < items->getCount(); i++ )
    {
        if ( !items->getItem( i )->isExcluded() )
        {
            result += formatItem( items->getItem( i ), sessionPath );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QString StepSession::formatItem
(
    Item    const * const item,
    QString const &       sessionPath
)
{
    QString    result    = QString( "# %1\n" ).arg( item->getName() );
    FileList   files     = session->getFiles()->getItemFiles( item, true, true );
    int        fileCount = files.count();
    QDir       sessionDirectory( sessionPath );

    if ( type == AbSession )
    {
        fileCount = qMin( fileCount, 2 );
    }

    if ( ( type == MushraSession ) && hiddenReference && files.value( 0 )->getVariant()->isReference() )
    {
        result += sessionDirectory.relativeFilePath( files.value( 0 )->getPathName() );
        result += "\n";
    }

    for ( int f = 0; f < fileCount; f++ )
    {
        result += sessionDirectory.relativeFilePath( files.value( f )->getPathName() );
        result += "\n";
    }

    return result;
}

/******************************************************************************/
