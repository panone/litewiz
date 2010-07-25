/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include "utility.h"
#include "file_collection.h"
#include "item_collection.h"
#include "variant_collection.h"

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

        VariantCollection const & getVariants
        (
            void
        );

        void classify
        (
            void
        );

    private:

        void setItems
        (
            int const variance
        );

        void setVariants
        (
            int const variance
        );

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

        void excludeVariants
        (
            QIntList const &       selection,
            bool             const exclude
        );

        void toggleReference
        (
            int const variant
        );

    signals:

        void fileCollectionUpdated
        (
            void
        );

        void itemCollectionUpdated
        (
            void
        );

        void variantCollectionUpdated
        (
            void
        );

        void classified
        (
            void
        );

    private:

        FileCollection      files;
        ItemCollection      items;
        VariantCollection   variants;

        Classifier        * classifier;
};

/******************************************************************************/

#endif /* SESSION_H */
