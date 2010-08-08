/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_H
#define FILE_CLUSTER_H

/******************************************************************************/

#include <QList>
#include <QString>

/*******************************************************************************
*******************************************************************************/
class FileCluster
{
    public:

        FileCluster
        (
            QString                const & name,
            QString                const & stem,
            QList< FileCluster * > const & collection
        );

    public:

        void setName
        (
            QString const & name
        );

        QString getName
        (
            void
        )
        const;

        QString getStem
        (
            void
        )
        const;

        int getIndex
        (
            void
        )
        const;

        void exclude
        (
            bool const exclude
        );

        bool isExcluded
        (
            void
        )
        const;

    private:

        QString                        name;
        QString                        stem;

        bool                           excluded;

        QList< FileCluster * > const & collection;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_H */
