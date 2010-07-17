/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/******************************************************************************/

#include <QList>
#include <QString>

/******************************************************************************/

class ClassifierImplementation;
class QStringList;

/*******************************************************************************
*******************************************************************************/
class ItemInfo
{
    public:

        QString        name;
        QString        stem;
        QList< int >   files;
};

/*******************************************************************************
*******************************************************************************/
class VariantInfo
{
    public:

        QString        name;
        QString        stem;
        QList< int >   files;
};

/*******************************************************************************
*******************************************************************************/
class Classifier
{
    public:

        Classifier
        (
            void
        );

        ~Classifier
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

        QList< ItemInfo > getItems
        (
            int variance
        );

        QList< VariantInfo > getVariants
        (
            int variance
        );

    private:

        ClassifierImplementation * implementation;

        int                        files;
};

/******************************************************************************/

#endif /* CLASSIFIER_H */
