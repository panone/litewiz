/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include "file_collection.h"
#include "item_collection.h"

/******************************************************************************/

class QStringList;

/*******************************************************************************
*******************************************************************************/
class Session : public QObject
{
    Q_OBJECT

    public:

        explicit Session
        (
            QObject * parent = 0
        );

    public:

        void loadFileList
        (
            QString const & fileName
        );

        void addFiles
        (
            QStringList const & fileNames
        );

        void addDirectory
        (
            QString const & fileName
        );

        FileCollection const & getFiles
        (
            void
        );

    private:

        QStringList getTextFileContents
        (
            QString const & fileName
        );

    signals:

        void fileCollectionUpdated
        (
            void
        );

    private:

        FileCollection   files;
        ItemCollection   items;
};

/******************************************************************************/

#endif /* SESSION_H */
