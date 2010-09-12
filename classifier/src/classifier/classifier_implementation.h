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

typedef QList< QIntList > QIntList2;
typedef QMap< int, int > QIntMap;
typedef QList< QIntMap > QIntMapList;
typedef QMap< int, float > QIntFloatMap;

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
            QIntMap const & clusterSize
        );

        QIntFloatMap getVarianceProbablity
        (
            QIntList const & factorVariance,
            QIntList const & frontVariance
        );

    private:

        QStringList    fileDescriptions;
        QIntMapList    clusters;
        QIntFloatMap   variance;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
