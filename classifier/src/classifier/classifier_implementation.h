/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QMap>
#include <QObject>
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
            Clusters
        };
};

/*******************************************************************************
*******************************************************************************/
class ClassifierImplementation : public QObject
{
    Q_OBJECT

    public:

        ClassifierImplementation
        (
            QStringList const &       fileNames,
            QObject           * const parent
        );

        ~ClassifierImplementation
        (
            void
        );

    public:

        int classify
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
