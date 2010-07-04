/*******************************************************************************
*******************************************************************************/

#ifndef CLASSIFIER_IMPLEMENTATION_H
#define CLASSIFIER_IMPLEMENTATION_H

/******************************************************************************/

#include <QObject>
#include <QStringList>

/*******************************************************************************
*******************************************************************************/
class ClassifierImplementation : public QObject
{
    Q_OBJECT

    public:

        ClassifierImplementation
        (
            QStringList const &       fileNames,
            QObject           * const parent
        );

    public:

        int classify
        (
            void
        );

    private:

        QStringList fileNames;
};

/******************************************************************************/

#endif /* CLASSIFIER_IMPLEMENTATION_H */
