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
class QUrl;
class Item;

typedef QList< File * > FileList;

/*******************************************************************************
*******************************************************************************/
class FileCollection
{
    private:

        static bool variantIndexCompare
        (
            File const * const file1,
            File const * const file2
        );

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

        void addUrls
        (
            QList< QUrl > const & urls
        );

        void removeFile
        (
            QString const & fileName
        );

        void removeDirectory
        (
            QString const & fileName
        );

        int getCount
        (
            void
        )
        const;

        int getIncludedCount
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
            Item const * const item,
            bool         const skipExcluded = false,
            bool         const referenceFirst = false
        )
        const;

        QStringList getNames
        (
            void
        )
        const;

    private:

        void addFile
        (
            QString const & fileName
        );

        void addFile
        (
            QFileInfo const & fileInfo
        );

        bool exists
        (
            File const * const file
        );

    private:

        FileList files;
};

/******************************************************************************/

#endif /* FILE_COLLECTION_H */
