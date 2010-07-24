/*******************************************************************************
*******************************************************************************/

#include <QAction>
#include <QMenu>
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
}

/*******************************************************************************
*******************************************************************************/
void VariantListView::populateContextMenu
(
    ContextMenuInfo const &       menuInfo,
    QMenu                 * const menu
)
{
    menu->addAction( setReferenceAction );
    menu->addSeparator();

    FileClusterListView::populateContextMenu( menuInfo, menu );
}

/******************************************************************************/
