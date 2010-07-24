/*******************************************************************************
*******************************************************************************/

#include <QList>
#include "classifier.h"
#include "utility.h"
#include "variant.h"
#include "variant_collection.h"

/*******************************************************************************
*******************************************************************************/
VariantCollection::~VariantCollection
(
    void
)
{
    qDeleteAll( variants );
}

/*******************************************************************************
*******************************************************************************/
Variant * VariantCollection::addVariant
(
    VariantInfo const & variantInfo
)
{
    Variant * variant = new Variant( variantInfo.name, variantInfo.stem );

    variants.append( variant );

    return variant;
}

/*******************************************************************************
*******************************************************************************/
int VariantCollection::getCount
(
    void
)
    const
{
    return variants.count();
}

/*******************************************************************************
*******************************************************************************/
Variant * VariantCollection::getVariant
(
    int const index
)
    const
{
    return variants.value( index );
}

/*******************************************************************************
*******************************************************************************/
void VariantCollection::clear
(
    void
)
{
    qDeleteAll( variants );

    variants.clear();
}

/*******************************************************************************
*******************************************************************************/
void VariantCollection::exclude
(
    QIntList const &       selection,
    bool             const exclude
)
{
    foreach ( int index, selection )
    {
        if ( ( index >= 0 ) && ( index < variants.count() ) )
        {
            variants[ index ]->exclude( exclude );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void VariantCollection::toggleReference
(
    int const variant
)
{
    if ( variants[ variant ]->isReference() )
    {
        variants[ variant ]->setReference( false );
    }
    else
    {
        foreach ( Variant * v, variants )
        {
            v->setReference( false );
        }

        variants[ variant ]->setReference( true );
    }
}

/******************************************************************************/
