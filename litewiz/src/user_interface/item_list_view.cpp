/*******************************************************************************
*******************************************************************************/

#include <QDebug>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
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
void ItemListView::excludeItems
(
    void
)
{
}

/*******************************************************************************
*******************************************************************************/
void ItemListView::includeItems
(
    void
)
{
}

/*******************************************************************************
*******************************************************************************/
void ItemListView::contextMenuEvent
(
    QContextMenuEvent * event
)
{
    QMenu menu( this );

    menu.addAction( excludeAction );
    menu.addAction( includeAction );

    menu.exec( event->globalPos() );
}

/******************************************************************************/
