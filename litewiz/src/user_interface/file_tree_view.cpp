/*******************************************************************************
*******************************************************************************/

#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QTreeView>
#include "file_tree_model.h"
#include "file_tree_view.h"

/*******************************************************************************
*******************************************************************************/
FileTreeView::FileTreeView
(
    QWidget * const parent
) :
    QTreeView( parent )
{
    createActions();
    connectSignals();
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::setModel
(
    FileTreeModel * model
)
{
    QTreeView::setModel( model );

    connect( this, SIGNAL( expanded( QModelIndex ) ), model, SLOT( expand( QModelIndex ) ) );
    connect( this, SIGNAL( collapsed( QModelIndex ) ), model, SLOT( collapse( QModelIndex ) ) );
    connect( this, SIGNAL( removeRequest( QModelIndexList ) ), model, SLOT( remove( QModelIndexList ) ) );
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::createActions
(
    void
)
{
    removeAction = new QAction( tr( "&Remove" ), this );
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::connectSignals
(
    void
)
{
    connect( removeAction, SIGNAL( triggered() ), this, SLOT( remove() ) );
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::remove
(
    void
)
{
    emit removeRequest( selectionModel()->selectedIndexes() );
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::reset
(
    void
)
{
    QTreeView::reset();

    QModelIndex index = model()->index( 0, 0 );

    while ( index.isValid() )
    {
        QVariant data = model()->data( index, FileTreeModel::ExpandedRole );

        if ( data.isValid() && data.toBool() )
        {
            expand( index );
        }

        index = model()->sibling( index.row() + 1, 0, index );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileTreeView::contextMenuEvent
(
    QContextMenuEvent * event
)
{
    if ( selectionModel()->hasSelection() )
    {
        QMenu menu( this );

        menu.addAction( removeAction );

        menu.exec( event->globalPos() );
    }
}

/******************************************************************************/
