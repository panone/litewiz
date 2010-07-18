/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include "utility.h"
#include "file_collection.h"
#include "item_collection.h"

/******************************************************************************/

class QStringList;
class Classifier;

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

        virtual ~Session
        (
            void
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

        ItemCollection const & getItems
        (
            void
        );

        void classify
        (
            void
        );

    private:

        QStringList getTextFileContents
        (
            QString const & fileName
        );

    public slots:

        void excludeItems
        (
            QIntList const &       selection,
            bool             const exclude
        );

    signals:

        void fileCollectionUpdated
        (
            void
        );

        void classified
        (
            void
        );

    private:

        FileCollection   files;
        ItemCollection   items;

        Classifier     * classifier;
};

/******************************************************************************/

#endif /* SESSION_H */
