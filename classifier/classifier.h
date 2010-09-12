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
class ClusterInfo
{
    public:

        QString        name;
        QString        stem;
        QList< int >   files;
};

/*******************************************************************************
*******************************************************************************/
class ItemInfo : public ClusterInfo
{
};

/*******************************************************************************
*******************************************************************************/
class VariantInfo : public ClusterInfo
{
    public:

        bool reference;
};

/*******************************************************************************
*******************************************************************************/
class ClassificationInfo
{
    public:

        QList< ItemInfo >      items;
        QList< VariantInfo >   variants;
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

        ClassificationInfo getClassification
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
