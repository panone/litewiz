/*******************************************************************************
*******************************************************************************/

#ifndef FILE_COLLECTION_H
#define FILE_COLLECTION_H

/******************************************************************************/

#include <QList>
#include <QString>
#include "file.h"

/******************************************************************************/

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

        void load
        (
            QString const & fileName
        );

        void append
        (
            QString const & filePath
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

        QStringList getTextFileContents
        (
            QString const & fileName
        );

    private:

        QList< File > files;
};

/******************************************************************************/

#endif /* FILE_COLLECTION_H */
