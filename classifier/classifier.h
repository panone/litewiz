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

    private:

        ClassifierImplementation * implementation;
};

/******************************************************************************/

#endif /* CLASSIFIER_H */
