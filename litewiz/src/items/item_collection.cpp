/*******************************************************************************
*******************************************************************************/

#include <QList>
#include "classifier.h"
#include "utility.h"
#include "item.h"
#include "item_collection.h"

/*******************************************************************************
*******************************************************************************/
ItemCollection::~ItemCollection
(
    void
)
{
    qDeleteAll( items );
}

/*******************************************************************************
*******************************************************************************/
Item * ItemCollection::addItem
(
    ItemInfo const & itemInfo
)
{
    Item * item = new Item( itemInfo.name, itemInfo.stem );

    items.append( item );

    return item;
}

/*******************************************************************************
*******************************************************************************/
int ItemCollection::getCount
(
    void
)
    const
{
    return items.count();
}

/*******************************************************************************
*******************************************************************************/
Item * ItemCollection::getItem
(
    int const index
)
    const
{
    return items.value( index );
}

/*******************************************************************************
*******************************************************************************/
void ItemCollection::clear
(
    void
)
{
    qDeleteAll( items );

    items.clear();
}

/*******************************************************************************
*******************************************************************************/
void ItemCollection::exclude
(
    QIntList const &       selection,
    bool             const exclude
)
{
    foreach ( int index, selection )
    {
        if ( ( index >= 0 ) && ( index < items.count() ) )
        {
            items[ index ]->exclude( exclude );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ItemCollection::move
(
    int              const target,
    QIntList const &       selection
)
{
    QList< Item * > reordered;
    int             reorderedTarget = -1;

    for ( int i = 0; i < items.count(); i++ )
    {
        if ( i == target )
        {
            reorderedTarget = reordered.count();
        }

        if ( selection.indexOf( i ) == -1 )
        {
            reordered.append( items[ i ] );
        }
    }

    if ( reorderedTarget == -1 )
    {
        reorderedTarget = reordered.count();
    }

    for ( int i = 0; i < selection.count(); i++ )
    {
        reordered.insert( reorderedTarget + i, items[ selection[ i ] ] );
    }

    items = reordered;
}

/******************************************************************************/
