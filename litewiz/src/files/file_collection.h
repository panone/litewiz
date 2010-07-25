/*******************************************************************************
*******************************************************************************/

#ifndef FILE_COLLECTION_H
#define FILE_COLLECTION_H

/******************************************************************************/

#include <QList>
#include "file.h"

/******************************************************************************/

class QString;
class QStringList;
class Item;

typedef QList< File * > FileList;

/*******************************************************************************
*******************************************************************************/
class FileCollection
{
    public:

        FileCollection
        (
            void
        );

        ~FileCollection
        (
            void
        );

    public:

        void addFiles
        (
            QStringList const & fileNames
        );

        void addDirectory
        (
            QString const & fileName
        );

        int getCount
        (
            void
        )
        const;

        File * getFile
        (
            int const index
        )
        const;

        FileList getAllFiles
        (
            void
        )
        const;

        FileList getItemFiles
        (
            Item const * const item
        )
        const;

        QStringList getNames
        (
            void
        )
        const;

    private:

        bool exists
        (
            File const * const file
        );

    private:

        FileList files;
};

/******************************************************************************/

#endif /* FILE_COLLECTION_H */
