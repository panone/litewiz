/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_H
#define CLASSIFIER_H

/******************************************************************************/

#include <QObject>

/******************************************************************************/

class ClassifierImplementation;
class QStringList;

/*******************************************************************************
*******************************************************************************/
class Classifier : public QObject
{
    Q_OBJECT

    public:

        Classifier
        (
            QStringList const &       fileNames,
            QObject           * const parent = 0
        );

    public:

        int classify
        (
            void
        );

    private:

        ClassifierImplementation * implementation;
};

/******************************************************************************/

#endif /* CLASSIFIER_H */
