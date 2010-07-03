/*******************************************************************************
*******************************************************************************/

#ifndef CONSOLE_H
#define CONSOLE_H

/******************************************************************************/

#include <QTextStream>

/*******************************************************************************
*******************************************************************************/
class Console
{
    public:

        static QTextStream & output
        (
            void
        );

        static QTextStream & input
        (
            void
        );

    public:

        Console
        (
            void
        );

        ~Console
        (
            void
        );

    private:

        static Console * instance;

    private:

        QTextStream   outputStream;
        QTextStream   inputStream;
};

/******************************************************************************/

#endif /* CONSOLE_H */
