/*******************************************************************************
*******************************************************************************/

#ifndef TEST_CASE_H
#define TEST_CASE_H

/******************************************************************************/

#include <QString>
#include <QStringList>

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

        bool validate
        (
            void
        );

        void loadFileNames
        (
            QString const & testSetPath
        );

        QString findFileNameList
        (
            QString const & testSetPath
        );

        QStringList getTextFileContents
        (
            QString const & fileName
        );

    private:

        bool          valid;
        QString       fileName;
        int           items;
        int           variants;
        QStringList   fileNames;
};

/******************************************************************************/

#endif /* TEST_CASE_H */
