/*******************************************************************************
*******************************************************************************/

#ifndef SESSION_H
#define SESSION_H

/******************************************************************************/

#include <QObject>
#include "utility.h"

/******************************************************************************/

class QStringList;
class QUrl;
class FileCollection;
class ItemCollection;
class VariantCollection;
class Classifier;

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

        void classify
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

        void setCurrentVariance
        (
            int const varianceIndex
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

        FileCollection    * files;
        ItemCollection    * items;
        VariantCollection * variants;

        Classifier        * classifier;

        QIntList            variance;
};

/******************************************************************************/

#endif /* SESSION_H */
