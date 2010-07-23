/*******************************************************************************
*******************************************************************************/

#include <QStringList>
#include "utility.h"
#include "classifier_implementation.h"

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::ClassifierImplementation
(
    void
)
{
}

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::~ClassifierImplementation
(
    void
)
{
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::classify
(
    QStringList const & fileNames
)
{
    this->fileNames = fileNames;

    extractClusters();

    QIntList   factorVariance = extractFactorVariance();
    QIntList   frontVariance  = extractFrontVariance();
}

/*******************************************************************************
*******************************************************************************/
int ClassifierImplementation::getDefaultVariance
(
    void
)
{
    return 42;
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::extractClusters
(
    void
)
{
    clusters.clear();

    foreach ( QString fileName1, fileNames )
    {
        ClusterSizeMap clusterSize;

        foreach ( QString fileName2, fileNames )
        {
            int offset = difference( fileName1, fileName2 );

            clusterSize[ offset ] += 1;
        }

        clusters.append( clusterSize );
    }
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::extractFactorVariance
(
    void
)
{
    QIntPairList   factors = pairFactor( fileNames.count() );
    QIntList       result;

    foreach ( QIntPair pair, factors )
    {
        result.append( pair.first );
        result.append( pair.second );
    }

    qSort( result );

    return result;
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::extractFrontVariance
(
    void
)
{
    QIntList            result;
    QList< QIntList >   accumulatedClusterSize;

    foreach ( ClusterSizeMap const & clusterSize, clusters )
    {
        accumulatedClusterSize.append( getAccumulatedClusterSize( clusterSize ) );
    }

    QIntList reference = accumulatedClusterSize.first();

    foreach ( int variance, reference )
    {
        bool valid = true;

        foreach ( QIntList size, accumulatedClusterSize )
        {
            if ( size.indexOf( variance ) == -1 )
            {
                valid = false;
                break;
            }
        }

        if ( valid )
        {
            result.append( variance );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::getAccumulatedClusterSize
(
    ClusterSizeMap const & clusterSize
)
{
    QIntList                           result;
    QMap< int, int >::const_iterator   i;
    int                                sum = 0;

    for ( i = clusterSize.constEnd(); i != clusterSize.constBegin(); )
    {
        sum += *( --i );

        result.append( sum );
    }

    return result;
}

/******************************************************************************/
