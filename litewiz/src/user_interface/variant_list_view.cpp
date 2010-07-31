/*******************************************************************************
*******************************************************************************/

#include <QAction>
#include <QMenu>
#include "context_menu_info.h"
#include "variant_list_model.h"
#include "file_cluster_list_view.h"
#include "variant_list_view.h"

/*******************************************************************************
*******************************************************************************/
VariantListView::VariantListView
(
    QWidget * const parent
) :
    FileClusterListView( parent )
{
    createActions();
    connectSignals();
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::setModel
(
    VariantListModel * model
)
{
    FileClusterListView::setModel( model );

    connect( this, SIGNAL( referenceChanged( QModelIndex ) ), model, SLOT( toggleReference( QModelIndex ) ) );
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::createActions
(
    void
)
{
    setReferenceAction = new QAction( tr( "&Reference" ), this );

    setReferenceAction->setCheckable( true );
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::connectSignals
(
    void
)
{
    connect( setReferenceAction, SIGNAL( triggered() ), this, SLOT( setReference() ) );
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::setReference
(
    void
)
{
    emit referenceChanged( selectedIndexes().first() );
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::populateContextMenu
(
    ContextMenuInfo const &       menuInfo,
    QMenu                 * const menu
)
{
    if ( menuInfo.hasMenuEntry( ContextMenuInfo::ReferenceChecked ) || menuInfo.hasMenuEntry( ContextMenuInfo::ReferenceUnchecked ) )
    {
        setReferenceAction->setChecked( menuInfo.hasMenuEntry( ContextMenuInfo::ReferenceChecked ) );

        menu->addAction( setReferenceAction );
        menu->addSeparator();
    }

    FileClusterListView::populateContextMenu( menuInfo, menu );
}

/******************************************************************************/
