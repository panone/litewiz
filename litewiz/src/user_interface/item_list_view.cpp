/*******************************************************************************
*******************************************************************************/

#include <QDebug>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include "utility.h"
#include "context_menu_info.h"
#include "item_list_view.h"

/*******************************************************************************
*******************************************************************************/
ItemListView::ItemListView
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
void ItemListView::createActions
(
    void
)
{
    excludeAction = new QAction( tr( "&Exclude" ), this );
    includeAction = new QAction( tr( "&Include" ), this );
}

/*******************************************************************************
*******************************************************************************/
void ItemListView::connectSignals
(
    void
)
{
    connect( excludeAction, SIGNAL( triggered() ), this, SLOT( excludeItems() ) );
    connect( includeAction, SIGNAL( triggered() ), this, SLOT( includeItems() ) );
}

/*******************************************************************************
*******************************************************************************/
QIntList ItemListView::getSelection
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
void ItemListView::excludeItems
(
    void
)
{
    emit excludeItemsRequest( getSelection(), true );
}

/*******************************************************************************
*******************************************************************************/
void ItemListView::includeItems
(
    void
)
{
    emit excludeItemsRequest( getSelection(), false );
}

/*******************************************************************************
*******************************************************************************/
void ItemListView::contextMenuEvent
(
    QContextMenuEvent * event
)
{
    ContextMenuInfo menuInfo( getSelection() );

    menuInfo.addMenuEntry( ContextMenuInfo::Exclude );
    menuInfo.addMenuEntry( ContextMenuInfo::Include );

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
