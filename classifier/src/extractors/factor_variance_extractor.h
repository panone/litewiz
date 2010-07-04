/*******************************************************************************
*******************************************************************************/

#ifndef FACTOR_VARIANCE_EXTRACTOR_H
#define FACTOR_VARIANCE_EXTRACTOR_H

/******************************************************************************/

#include <QVariant>
#include "extractor.h"

/******************************************************************************/

class ClassifierImplementation;

/*******************************************************************************
*******************************************************************************/
class FactorVarianceExtractor : public Extractor
{
    public:

        FactorVarianceExtractor
        (
            ClassifierImplementation * const classifier
        );

    public:

        virtual void extract
        (
            void
        );

        virtual QVariantList getData
        (
            void
        );

    private:

        QVariantList variance;
};

/******************************************************************************/

#endif /* FACTOR_VARIANCE_EXTRACTOR_H */
