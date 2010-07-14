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

/*******************************************************************************
*******************************************************************************/
class FileCollection
{
    public:

        typedef QList< File >::const_iterator const_iterator;

    public:

        FileCollection
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

        int getFileCount
        (
            void
        );

        const_iterator begin
        (
            void
        )
        const;

        const_iterator end
        (
            void
        )
        const;

    private:

        QList< File > files;
};

/******************************************************************************/

#endif /* FILE_COLLECTION_H */
