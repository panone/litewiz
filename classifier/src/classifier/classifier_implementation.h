/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QList>
#include <QMap>
#include <QStringList>
#include "utility.h"

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

    private:

        QStringList                 fileNames;
        QList< QMap< int, int > >   clusters;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
