/*******************************************************************************
*******************************************************************************/

#include <QDebug>
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

/******************************************************************************/
