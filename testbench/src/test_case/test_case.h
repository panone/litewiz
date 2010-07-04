/*******************************************************************************
*******************************************************************************/

#ifndef TEST_CASE_H
#define TEST_CASE_H

/******************************************************************************/

#include <QString>

/******************************************************************************/

class QDomElement;

/*******************************************************************************
*******************************************************************************/
class TestCase
{
    public:

        TestCase
        (
            QString     const & testSetPath,
            QDomElement const & definition
        );

    public:

        bool isValid
        (
            void
        );

        bool run
        (
            void
        );

    private:

        void validate
        (
            QString const & testSetPath
        );

        void loadFileNames
        (
            void
        );

    private:

        bool      valid;
        QString   fileName;
        int       items;
        int       variants;
};

/******************************************************************************/

#endif /* TEST_CASE_H */
