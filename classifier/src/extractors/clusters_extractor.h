/*******************************************************************************
*******************************************************************************/

#ifndef CLUSTERS_EXTRACTOR_H
#define CLUSTERS_EXTRACTOR_H

/******************************************************************************/

#include <QVariant>
#include "extractor.h"

/******************************************************************************/

class ClassifierImplementation;

/*******************************************************************************
*******************************************************************************/
class ClustersExtractor : public Extractor
{
    public:

        ClustersExtractor
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

    protected:

        QVariantList clusters;
};

/******************************************************************************/

#endif /* CLUSTERS_EXTRACTOR_H */
