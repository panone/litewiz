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
