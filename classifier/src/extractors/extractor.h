/*******************************************************************************
*******************************************************************************/

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

/******************************************************************************/

#include <QVariant>

/******************************************************************************/

class ClassifierImplementation;

/*******************************************************************************
*******************************************************************************/
class Extractor
{
    public:

        Extractor
        (
            ClassifierImplementation * const classifier
        );

        virtual ~Extractor
        (
            void
        );

    public:

        virtual void extract
        (
            void
        )
        = 0;

        virtual QVariantList getData
        (
            void
        )
        = 0;

    protected:

        ClassifierImplementation * classifier;
};

/******************************************************************************/

#endif /* EXTRACTOR_H */
