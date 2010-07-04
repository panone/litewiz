/*******************************************************************************
*******************************************************************************/

#ifndef TEST_BENCH_H
#define TEST_BENCH_H

/******************************************************************************/

#include <QObject>

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
            QDomElement const & testSet
        );

    signals:

        void finished
        (
            void
        );
};

/******************************************************************************/

#endif /* TEST_BENCH_H */
