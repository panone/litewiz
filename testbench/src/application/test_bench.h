/*******************************************************************************
*******************************************************************************/

#ifndef TEST_BENCH_H
#define TEST_BENCH_H

/******************************************************************************/

#include <QList>
#include <QObject>
#include "test_case.h"

/******************************************************************************/

class QDomElement;
class QSrting;

/*******************************************************************************
*******************************************************************************/
class TestBench : public QObject
{
    Q_OBJECT

    public:

        TestBench
        (
            QObject * const parent
        );

    public:

        void run
        (
            QString const & fileName
        );

    private:

        void loadTestSet
        (
            QString const & fileName
        );

        void loadTestCases
        (
            QString     const & testSetPath,
            QDomElement const & testSet
        );

    signals:

        void finished
        (
            void
        );

    private:

        QList< TestCase > testCases;
};

/******************************************************************************/

#endif /* TEST_BENCH_H */
