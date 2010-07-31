/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_COLLECTION_H
#define FILE_CLUSTER_COLLECTION_H

/******************************************************************************/

#include <QList>
#include "utility.h"

/******************************************************************************/

class FileCluster;
class ClassificationInfo;

/*******************************************************************************
*******************************************************************************/
class FileClusterCollection
{
    protected:

        ~FileClusterCollection
        (
            void
        );

    public:

        FileCluster * getCluster
        (
            int const index
        )
        const;

        int getCount
        (
            void
        )
        const;

        void clear
        (
            void
        );

        void exclude
        (
            QIntList const &       selection,
            bool             const exclude
        );

        void move
        (
            int              const target,
            QIntList const &       selection
        );

    protected:

        QList< FileCluster * > clusters;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_COLLECTION_H */
