/*******************************************************************************
*******************************************************************************/

#ifndef EXTRACTOR_H
#define EXTRACTOR_H

/******************************************************************************/

#include <QList>
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

    public:

        virtual void extract
        (
            void
        )
        = 0;

        virtual QList< QVariant > getData
        (
            void
        )
        = 0;

    protected:

        ClassifierImplementation * classifier;
};

/******************************************************************************/

#endif /* EXTRACTOR_H */
