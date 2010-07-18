/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_H
#define VARIANT_H

/******************************************************************************/

#include <QString>

/*******************************************************************************
*******************************************************************************/
class Variant
{
    public:

        Variant
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

        void setReference
        (
            bool const reference
        );

        bool isReference
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

        bool      reference;
        bool      excluded;
};

/******************************************************************************/

#endif /* VARIANT_H */
