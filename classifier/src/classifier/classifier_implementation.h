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

        void extractClusters
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

        void detectUniqueTrackClusterSize
        (
            QIntSet const & clusterSize
        );

        void detectUnmatchedClusterSize
        (
            QIntSet const & clusterSize
        );

        void detectSingleTrack1
        (
            QIntSet const & clusterSize
        );

        void detectTrackClusterSize
        (
            StemInfoList const & stemClusterInfo
        );

        void detectSingleTrack2
        (
            StemInfoList const & stemClusterInfo
        );

        void applyVarianceProbability
        (
            QIntFloatMap const & varianceProbability
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
