/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_COLLECTION_H
#define VARIANT_COLLECTION_H

/******************************************************************************/

#include "file_cluster_collection.h"

/******************************************************************************/

class FileCluster;
class Variant;
class VariantInfo;

/*******************************************************************************
*******************************************************************************/
class VariantCollection : public FileClusterCollection
{
    public:

        Variant * addVariant
        (
            VariantInfo const & variantInfo
        );

        Variant * getVariant
        (
            int const index
        )
        const;

        void toggleReference
        (
            int const index
        );

    public:

        Variant * getVariant
        (
            FileCluster * const cluster
        )
        const;
};

/******************************************************************************/

#endif /* VARIANT_COLLECTION_H */
