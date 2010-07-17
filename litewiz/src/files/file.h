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

        QString getItemName
        (
            void
        )
        const;

        QString getVariantName
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
