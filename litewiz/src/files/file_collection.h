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

        int getCount
        (
            void
        );

        QStringList getNames
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

        File & operator[]
        (
            int const index
        );

    private:

        QList< File > files;
};

/******************************************************************************/

#endif /* FILE_COLLECTION_H */
