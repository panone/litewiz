/*******************************************************************************
*******************************************************************************/

#include "classifier.h"
#include "item.h"
#include "file_cluster_collection.h"
#include "item_collection.h"

/*******************************************************************************
*******************************************************************************/
Item * ItemCollection::addItem
(
    ItemInfo const & itemInfo
)
{
    Item * item = new Item( itemInfo.name, itemInfo.stem );

    clusters.append( item );

    return item;
}

/*******************************************************************************
*******************************************************************************/
Item * ItemCollection::getItem
(
    int const index
)
    const
{
    return static_cast< Item * >( clusters.value( index ) );
}

/******************************************************************************/
