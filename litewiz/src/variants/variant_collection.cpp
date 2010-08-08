/*******************************************************************************
*******************************************************************************/

#include "classifier.h"
#include "variant.h"
#include "file_cluster_collection.h"
#include "variant_collection.h"

/*******************************************************************************
*******************************************************************************/
Variant * VariantCollection::addVariant
(
    VariantInfo const & variantInfo
)
{
    Variant * variant = new Variant( variantInfo.name, variantInfo.stem, clusters );

    clusters.append( variant );

    return variant;
}

/*******************************************************************************
*******************************************************************************/
Variant * VariantCollection::getVariant
(
    int const index
)
    const
{
    return getVariant( clusters.value( index ) );
}

/*******************************************************************************
*******************************************************************************/
void VariantCollection::toggleReference
(
    int const index
)
{
    if ( getVariant( index )->isReference() )
    {
        getVariant( index )->setReference( false );
    }
    else
    {
        foreach ( FileCluster * cluster, clusters )
        {
            getVariant( cluster )->setReference( false );
        }

        getVariant( index )->setReference( true );
    }
}

/*******************************************************************************
*******************************************************************************/
Variant * VariantCollection::getVariant
(
    FileCluster * const cluster
)
    const
{
    return static_cast< Variant * >( cluster );
}

/******************************************************************************/
