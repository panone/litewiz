/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_COLLECTION_H
#define ITEM_COLLECTION_H

/******************************************************************************/

#include <QList>
#include "utility.h"

/******************************************************************************/

class Item;
class ItemInfo;

/*******************************************************************************
*******************************************************************************/
class ItemCollection
{
    public:

        ~ItemCollection
        (
            void
        );

    public:

        Item * addItem
        (
            ItemInfo const & itemInfo
        );

        int getCount
        (
            void
        )
        const;

        Item * getItem
        (
            int const index
        )
        const;

        void clear
        (
            void
        );

        void exclude
        (
            QIntList const &       selection,
            bool             const exclude
        );

    private:

        QList< Item * > items;
};

/******************************************************************************/

#endif /* ITEM_COLLECTION_H */
