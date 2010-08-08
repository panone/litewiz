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
class ClassificationInfo
{
    public:

        QString        name;
        QString        stem;
        QList< int >   files;
};

/*******************************************************************************
*******************************************************************************/
class ItemInfo : public ClassificationInfo
{
};

/*******************************************************************************
*******************************************************************************/
class VariantInfo : public ClassificationInfo
{
    public:

        bool reference;
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

        QList< int > getPossibleVariance
        (
            void
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
        QList< int >               variance;
};

/******************************************************************************/

#endif /* CLASSIFIER_H */
