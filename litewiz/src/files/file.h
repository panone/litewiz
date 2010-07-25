/*******************************************************************************
*******************************************************************************/

#ifndef FILE_H
#define FILE_H

/******************************************************************************/

#include <QFileInfo>
#include <QString>

/******************************************************************************/

class Item;
class Variant;

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

        QString getPathName
        (
            void
        )
        const;

        void setItem
        (
            Item * const item
        );

        Item const * getItem
        (
            void
        )
        const;

        void setVariant
        (
            Variant * const variant
        );

        Variant const * getVariant
        (
            void
        )
        const;

        bool operator==
        (
            File const & file
        )
        const;

    private:

        QFileInfo   info;
        Item      * item;
        Variant   * variant;
};

/******************************************************************************/

#endif /* FILE_H */
