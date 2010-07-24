/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_H
#define FILE_CLUSTER_H

/******************************************************************************/

#include <QString>

/*******************************************************************************
*******************************************************************************/
class FileCluster
{
    public:

        FileCluster
        (
            QString const & name,
            QString const & stem
        );

    public:

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

        QString   name;
        QString   stem;

        bool      excluded;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_H */
