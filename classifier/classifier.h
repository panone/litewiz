/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/******************************************************************************/

class ClassifierImplementation;
class QStringList;

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

    private:

        ClassifierImplementation * implementation;
};

/******************************************************************************/

#endif /* CLASSIFIER_H */
