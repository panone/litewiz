/*******************************************************************************
*******************************************************************************/

#include <QVariant>
#include "classifier_implementation.h"
#include "utility.h"
#include "extractor.h"
#include "factor_variance_extractor.h"

/*******************************************************************************
*******************************************************************************/
FactorVarianceExtractor::FactorVarianceExtractor
(
    ClassifierImplementation * const classifier
) :
    Extractor( classifier )
{
}

/*******************************************************************************
*******************************************************************************/
void FactorVarianceExtractor::extract
(
    void
)
{
    variance.clear();

    QVariantList   fileNames = classifier->getData( ClassifierData::FileNames );
    QIntPairList   factors   = pairFactor( fileNames.count() );

    QIntList list;

    foreach ( QIntPair pair, factors )
    {
        list.append( pair.first );
        list.append( pair.second );
    }

    qSort( list );

    foreach ( int factor, list )
    {
        variance.append( factor );
    }
}

/*******************************************************************************
*******************************************************************************/
QVariantList FactorVarianceExtractor::getData
(
    void
)
{
    return variance;
}

/******************************************************************************/
