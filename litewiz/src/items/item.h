/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_H
#define ITEM_H

/******************************************************************************/

#include <QString>

/*******************************************************************************
*******************************************************************************/
class Item
{
    public:

        Item
        (
            QString const & name,
            QString const & stem
        );

    public:

        QString getName
        (
            void
        )
        const;

        QString getStem
        (
            void
        )
        const;

    private:

        QString   name;
        QString   stem;
};

/******************************************************************************/

#endif /* ITEM_H */
