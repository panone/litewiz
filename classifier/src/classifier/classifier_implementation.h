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

    private:

        QStringList               fileNames;
        QList< ClusterSizeMap >   clusters;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
