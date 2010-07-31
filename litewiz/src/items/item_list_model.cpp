/*******************************************************************************
*******************************************************************************/

#include "session.h"
#include "item_collection.h"
#include "file_cluster_list_model.h"
#include "item_list_model.h"

/*******************************************************************************
*******************************************************************************/
ItemListModel::ItemListModel
(
    Session * const session,
    QObject * const parent
) :
    FileClusterListModel( session->getItems(), parent )
{
    connect( session, SIGNAL( classified() ), this, SLOT( update() ) );
}

/******************************************************************************/
