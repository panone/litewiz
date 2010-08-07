/*******************************************************************************
*******************************************************************************/

#include <QAction>
#include <QContextMenuEvent>
#include <QListView>
#include <QMenu>
#include "utility.h"
#include "context_menu_info.h"
#include "file_cluster_list_model.h"
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
void FileClusterListView::setModel
(
    FileClusterListModel * model
)
{
    QListView::setModel( model );

    connect( this, SIGNAL( contextMenuRequest( ContextMenuInfo * const ) ), model, SLOT( initContextMenu( ContextMenuInfo * const ) ) );
    connect( this, SIGNAL( excludeRequest( QIntList, bool ) ), model, SLOT( exclude( QIntList, bool ) ) );

    connect( model, SIGNAL( selectionMoved( QItemSelection ) ), this, SLOT( setSelection( QItemSelection ) ) );
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
    renameAction  = new QAction( tr( "&Rename" ), this );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::connectSignals
(
    void
)
{
    connect( excludeAction, SIGNAL( triggered() ), this, SLOT( exclude() ) );
    connect( includeAction, SIGNAL( triggered() ), this, SLOT( include() ) );
    connect( renameAction, SIGNAL( triggered() ), this, SLOT( rename() ) );
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
void FileClusterListView::exclude
(
    void
)
{
    emit excludeRequest( getSelection(), true );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::include
(
    void
)
{
    emit excludeRequest( getSelection(), false );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::rename
(
    void
)
{
    edit( selectedIndexes().first() );
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListView::setSelection
(
    QItemSelection const & selection
)
{
    selectionModel()->select( selection, QItemSelectionModel::ClearAndSelect );
    selectionModel()->setCurrentIndex( selection.indexes().first(), QItemSelectionModel::Select );
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

    populateContextMenu( menuInfo, &menu );

    menu.exec( event->globalPos() );
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
void FileClusterListView::populateContextMenu
(
    ContextMenuInfo const &       menuInfo,
    QMenu                 * const menu
)
{
    if ( menuInfo.hasMenuEntry( ContextMenuInfo::Exclude ) )
    {
        menu->addAction( excludeAction );
    }

    if ( menuInfo.hasMenuEntry( ContextMenuInfo::Include ) )
    {
        menu->addAction( includeAction );
    }

    if ( menuInfo.hasMenuEntry( ContextMenuInfo::Rename ) )
    {
        menu->addSeparator();
        menu->addAction( renameAction );
    }
}

/******************************************************************************/
