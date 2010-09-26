/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QList>
#include <QMap>
#include <QSet>
#include <QStringList>
#include "utility.h"

/******************************************************************************/

class ClassificationInfo;
class StemInfo;

/******************************************************************************/

typedef QList< QIntList > QIntList2;
typedef QMap< int, int > QIntMap;
typedef QMapIterator< int, int > QIntMapIterator;
typedef QList< QIntMap > QIntMapList;
typedef QMap< int, float > QIntFloatMap;
typedef QMapIterator< int, float > QIntFloatMapIterator;
typedef QMap< QString, int > QStringIntMap;
typedef QMap< QString, QIntList > QStringIntListMap;
typedef QMap< QString, QString > QStringMap;
typedef QSet< QString > QStringSet;
typedef QList< StemInfo > StemInfoList;

/*******************************************************************************
*******************************************************************************/
class StemInfo
{
    public:

        int       stemLength;
        int       clusters;
        QIntSet   clusterSize;
};

/*******************************************************************************
*******************************************************************************/
class ClassifierImplementation
{
    public:

        void classify
        (
            QStringList const & fileNames
        );

        QIntList getPossibleVariance
        (
            void
        );

        int getDefaultVariance
        (
            void
        );

        ClassificationInfo getClassification
        (
            int const variance
        );

    private:

        void initializeFileDescriptions
        (
            QStringList const & fileNames
        );

        void initializeClusters
        (
            void
        );

        QIntFloatMap getVarianceProbablity
        (
            void
        );

        QIntMap getClusterSizeCount
        (
            void
        );

        QIntSet getUnmatchedClusterSize
        (
            void
        );

        StemInfoList getStemClusterInfo
        (
            void
        );

        void initializeVariance
        (
            QIntFloatMap const & varianceProbability
        );

        void addVarianceProbability
        (
            int   const variance,
            float const probability
        );

        void detectPopularClusterSizes1
        (
            void
        );

        QIntList getAccumulatedClusterSize
        (
            QIntMap const & clusterSize
        );

        void detectPopularClusterSizes2
        (
            QIntMap const & clusterSizeCount
        );

        void detectClusterSizeStep
        (
            QIntMap const & clusterSizeCount
        );

        QIntList getRelevantClusterSizes
        (
            QIntList const & clusterSize
        );

        void detectUniqueItemClusterSize
        (
            QIntSet const & clusterSize
        );

        void detectUnmatchedClusterSize
        (
            QIntSet const & clusterSize
        );

        void detectSingleItem1
        (
            QIntSet const & clusterSize
        );

        void detectItemClusterSize
        (
            StemInfoList const & stemClusterInfo
        );

        void detectSingleItem2
        (
            StemInfoList const & stemClusterInfo
        );

        void applyVarianceProbability
        (
            QIntFloatMap const & varianceProbability
        );

        void validateVariance
        (
            void
        );

        QIntList getSplitIndices
        (
            int const variance
        );

        QStringMap getItemNames
        (
            QStringList const & stems
        );

        QStringMap getVariantNames
        (
            QStringList const & stems
        );

        float accumulateProbability
        (
            QIntFloatMap const & probability
        );

    private:

        QStringList    fileDescriptions;
        QIntMapList    clusters;
        QIntFloatMap   variance;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
