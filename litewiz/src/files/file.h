/*******************************************************************************
*******************************************************************************/

#ifndef FILE_H
#define FILE_H

/******************************************************************************/

#include <QFileInfo>
#include <QString>

/*******************************************************************************
*******************************************************************************/
class File
{
    public:

        File
        (
            QString const & path
        );

    public:

        QString getPath
        (
            void
        );

        QString getName
        (
            void
        );

        QString getItem
        (
            void
        );

        QString getVariant
        (
            void
        );

    private:

        QFileInfo info;
};

/******************************************************************************/

#endif /* FILE_H */
