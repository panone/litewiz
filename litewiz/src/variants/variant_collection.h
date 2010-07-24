/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_COLLECTION_H
#define VARIANT_COLLECTION_H

/******************************************************************************/

#include <QList>
#include "utility.h"

/******************************************************************************/

class Variant;
class VariantInfo;

/*******************************************************************************
*******************************************************************************/
class VariantCollection
{
    public:

        ~VariantCollection
        (
            void
        );

    public:

        Variant * addVariant
        (
            VariantInfo const & variantInfo
        );

        int getCount
        (
            void
        )
        const;

        Variant * getVariant
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

        void toggleReference
        (
            int const variant
        );

    private:

        QList< Variant * > variants;
};

/******************************************************************************/

#endif /* VARIANT_COLLECTION_H */
