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
class ClassifierImplementation : public QObject
{
    Q_OBJECT

    public:

        enum DataIdentifier
        {
            FileNames,
            Clusters
        };

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
            DataIdentifier const identifier
        );

    private:

        QStringList                           fileNames;

        QMap< DataIdentifier, Extractor * >   extractors;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
