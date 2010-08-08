/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_H
#define VARIANT_H

/******************************************************************************/

#include "file_cluster.h"

/******************************************************************************/

class QString;

/*******************************************************************************
*******************************************************************************/
class Variant : public FileCluster
{
    public:

        Variant
        (
            QString                const & name,
            QString                const & stem,
            QList< FileCluster * > const & collection
        );

    public:

        void setReference
        (
            bool const reference
        );

        bool isReference
        (
            void
        )
        const;

    private:

        bool reference;
};

/******************************************************************************/

#endif /* VARIANT_H */
