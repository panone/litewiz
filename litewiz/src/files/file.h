/*******************************************************************************
*******************************************************************************/

#ifndef FILE_H
#define FILE_H

/******************************************************************************/

#include <QFileInfo>
#include <QString>

/******************************************************************************/

class Item;

/*******************************************************************************
*******************************************************************************/
class File
{
    public:

        explicit File
        (
            QString const & fileName
        );

        explicit File
        (
            QFileInfo const & fileInfo
        );

    public:

        QString getPath
        (
            void
        )
        const;

        QString getName
        (
            void
        )
        const;

        void setItem
        (
            Item * const item
        );

        QString getItem
        (
            void
        )
        const;

        QString getVariant
        (
            void
        )
        const;

    private:

        QFileInfo   info;
        Item      * item;
};

/******************************************************************************/

#endif /* FILE_H */
