/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include "file_collection.h"

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

    signals:

        void fileCollectionUpdated
        (
            void
        );

    private:

        FileCollection files;
};

/******************************************************************************/

#endif /* SESSION_H */
