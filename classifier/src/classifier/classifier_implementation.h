/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QList>
#include <QMap>
#include <QStringList>
#include "utility.h"

/******************************************************************************/

typedef QMap< int, int > ClusterSizeMap;
typedef QMap< int, float > VarianceProbability;

/*******************************************************************************
*******************************************************************************/
class ClassifierImplementation
{
    public:

        ClassifierImplementation
        (
            void
        );

        ~ClassifierImplementation
        (
            void
        );

    public:

        void classify
        (
            QStringList const & fileNames
        );

        int getDefaultVariance
        (
            void
        );

    private:

        void extractClusters
        (
            void
        );

        QIntList extractFactorVariance
        (
            void
        );

        QIntList extractFrontVariance
        (
            void
        );

        QIntList getAccumulatedClusterSize
        (
            ClusterSizeMap const & clusterSize
        );

        VarianceProbability getVarianceProbablity
        (
            QIntList const & factorVariance,
            QIntList const & frontVariance
        );

    private:

        QStringList               fileNames;
        QList< ClusterSizeMap >   clusters;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
