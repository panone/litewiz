/*******************************************************************************
*******************************************************************************/

#include <QDebug>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include "utility.h"
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
    bool   exclude = true;
    bool   include = true;

    emit contextMenuRequest( getSelection(), &exclude, &include );

    QMenu menu( this );

    if ( exclude )
    {
        menu.addAction( excludeAction );
    }

    if ( include )
    {
        menu.addAction( includeAction );
    }

    menu.exec( event->globalPos() );
}

/******************************************************************************/
