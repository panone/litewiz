/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include <QSet>
#include "utility.h"

/******************************************************************************/

class QStringList;
class QUrl;
class FileCollection;
class ItemCollection;
class VariantCollection;
class Classifier;
class ClassificationInfo;
class FileTreeItem;

/*******************************************************************************
*******************************************************************************/
class Session : public QObject
{
    Q_OBJECT

    public:

        explicit Session
        (
            QObject * const parent = 0
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

        void addUrls
        (
            QList< QUrl > const & fileName
        );

        void removeFiles
        (
            QSet< FileTreeItem * > const & items
        );

        FileCollection * getFiles
        (
            void
        );

        ItemCollection * getItems
        (
            void
        );

        VariantCollection * getVariants
        (
            void
        );

        QIntList getPossibleVariance
        (
            void
        );

        int getCurrentVariance
        (
            void
        );

    private:

        void applySettings
        (
            void
        );

        void updateFileCollection
        (
            ConstRunnable const & update
        );

        void setItems
        (
            ClassificationInfo const & classification
        );

        void setVariants
        (
            ClassificationInfo const & classification
        );

        void invalidateClassification
        (
            void
        );

        QStringList getTextFileContents
        (
            QString const & fileName
        );

    public slots:

        void loadSettings
        (
            void
        );

        void classify
        (
            void
        );

        void setCurrentVariance
        (
            int const varianceIndex
        );

    signals:

        void fileCollectionUpdated
        (
            void
        );

        void classificationChanged
        (
            void
        );

    private:

        FileCollection    * files;
        ItemCollection    * items;
        VariantCollection * variants;

        bool                autoClassify;
        bool                classified;
        Classifier        * classifier;

        QIntList            variance;
};

/******************************************************************************/

#endif /* SESSION_H */
