/*******************************************************************************
*******************************************************************************/

#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include "utility.h"
#include "context_menu_info.h"
#include "file_cluster_list_view.h"

/*******************************************************************************
*******************************************************************************/
FileClusterListView::FileClusterListView
(
    QWidget * const parent
) :
    QListView( parent )
{
    createActions();
    connectSignals();
}

/*******************************************************************************
*******************************************************************************/
QIntList FileClusterListView::getSelection
(
    void
)
{
    QIntList result;

    foreach ( QModelIndex const & index, selectedIndexes() )
    {
        result.append( index.row() );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
ContextMenuInfo FileClusterListView::getDefaultContextMenu
(
    void
)
{
    ContextMenuInfo result( getSelection() );

    result.addMenuEntry( ContextMenuInfo::Exclude );
    result.addMenuEntry( ContextMenuInfo::Include );

    return result;
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::excludeItems
(
    void
)
{
    emit excludeItemsRequest( getSelection(), true );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::includeItems
(
    void
)
{
    emit excludeItemsRequest( getSelection(), false );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::createActions
(
    void
)
{
    excludeAction = new QAction( tr( "&Exclude" ), this );
    includeAction = new QAction( tr( "&Include" ), this );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::connectSignals
(
    void
)
{
    connect( excludeAction, SIGNAL( triggered() ), this, SLOT( excludeItems() ) );
    connect( includeAction, SIGNAL( triggered() ), this, SLOT( includeItems() ) );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::contextMenuEvent
(
    QContextMenuEvent * event
)
{
    ContextMenuInfo menuInfo = getDefaultContextMenu();

    emit contextMenuRequest( &menuInfo );

    QMenu menu( this );

    if ( menuInfo.hasMenuEntry( ContextMenuInfo::Exclude ) )
    {
        menu.addAction( excludeAction );
    }

    if ( menuInfo.hasMenuEntry( ContextMenuInfo::Include ) )
    {
        menu.addAction( includeAction );
    }

    menu.exec( event->globalPos() );
}

/******************************************************************************/
