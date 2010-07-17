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

    QIntList factorVariance = extractFactorVariance();
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
        QMap< int, int > clusterSize;

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
    QIntPairList factors = pairFactor( fileNames.count() );

    QIntList result;

    foreach ( QIntPair pair, factors )
    {
        result.append( pair.first );
        result.append( pair.second );
    }

    qSort( result );

    return result;
}

/******************************************************************************/
