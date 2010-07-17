/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QMap>
#include <QStringList>
#include <QVariant>
#include "extractor.h"

/*******************************************************************************
*******************************************************************************/
class ClassifierData
{
    public:

        enum Identifier
        {
            FileNames,
            Clusters,
            FactorVariance
        };
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

        int getDefaultVariance
        (
            void
        );

        QVariantList getData
        (
            ClassifierData::Identifier const identifier
        );

    private:

        QStringList                                       fileNames;

        QMap< ClassifierData::Identifier, Extractor * >   extractors;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
