/*******************************************************************************
*******************************************************************************/

#include <QObject>
#include <QStringList>
#include <QVariant>
#include "extractor.h"
#include "clusters_extractor.h"
#include "factor_variance_extractor.h"
#include "classifier_implementation.h"

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::ClassifierImplementation
(
    QStringList const &       fileNames,
    QObject           * const parent
) :
    QObject( parent ),
    fileNames( fileNames )
{
    extractors[ ClassifierData::Clusters ] = new ClustersExtractor( this );
    extractors[ ClassifierData::FactorVariance ] = new FactorVarianceExtractor( this );
}

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::~ClassifierImplementation
(
    void
)
{
    foreach ( Extractor * extractor, extractors )
    {
        delete extractor;
    }
}

/*******************************************************************************
*******************************************************************************/
int ClassifierImplementation::classify
(
    void
)
{
    foreach ( Extractor * extractor, extractors )
    {
        extractor->extract();
    }

    return 42;
}

/*******************************************************************************
*******************************************************************************/
QVariantList ClassifierImplementation::getData
(
    ClassifierData::Identifier const identifier
)
{
    QVariantList result;

    if ( identifier == ClassifierData::FileNames )
    {
        foreach ( QString fileName, fileNames )
        {
            result.append( fileName );
        }
    }
    else
    {
        result = extractors[ identifier ]->getData();
    }

    return result;
}

/******************************************************************************/
