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
    extractClusters( fileNames );
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
    QStringList const & fileNames
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

/******************************************************************************/
