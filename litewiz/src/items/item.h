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

        void exclude
        (
            bool const exclude
        );

        bool isExcluded
        (
            void
        )
        const;

    private:

        QString   name;
        QString   stem;

        bool      excluded;
};

/******************************************************************************/

#endif /* ITEM_H */
