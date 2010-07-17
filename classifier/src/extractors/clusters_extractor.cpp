/*******************************************************************************
*******************************************************************************/

#include <QMap>
#include <QVariant>
#include "classifier_implementation.h"
#include "utility.h"
#include "extractor.h"
#include "clusters_extractor.h"

/*******************************************************************************
*******************************************************************************/
ClustersExtractor::ClustersExtractor
(
    ClassifierImplementation * const classifier
) :
    Extractor( classifier )
{
}

/*******************************************************************************
*******************************************************************************/
void ClustersExtractor::extract
(
    void
)
{
    clusters.clear();

    QVariantList fileNames;// = classifier->getData( ClassifierData::FileNames );

    foreach ( QVariant fileName1, fileNames )
    {
        QMap< int, int > clusterSize;

        foreach ( QVariant fileName2, fileNames )
        {
            int offset = difference( fileName1.toString(), fileName2.toString() );

            clusterSize[ offset ] += 1;
        }

        clusters.append( wrap( clusterSize ) );
    }
}

/*******************************************************************************
*******************************************************************************/
QVariantList ClustersExtractor::getData
(
    void
)
{
    return clusters;
}

/*******************************************************************************
*******************************************************************************/
QVariant ClustersExtractor::wrap
(
    QMap< int, int > const & clusterSize
)
{
    QVariantList result;

    foreach ( int offset, clusterSize.keys() )
    {
        QVariantList pair;

        pair.append( offset );
        pair.append( clusterSize[ offset ] );

        result.append( QVariant( pair ) );
    }

    return QVariant( result );
}

/******************************************************************************/
