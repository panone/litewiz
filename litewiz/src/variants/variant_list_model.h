/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_LIST_MODEL_H
#define VARIANT_LIST_MODEL_H

/******************************************************************************/

#include "file_cluster_list_model.h"

/******************************************************************************/

class ContextMenuInfo;
class Session;
class VariantCollection;

/*******************************************************************************
*******************************************************************************/
class VariantListModel : public FileClusterListModel
{
    Q_OBJECT

    public:

        VariantListModel
        (
            Session * const session,
            QObject * const parent = 0
        );

    public slots:

        void initContextMenu
        (
            ContextMenuInfo * const menuInfo
        );

        void toggleReference
        (
            QModelIndex const & index
        );

    private:

        virtual QVariant getData
        (
            int const index,
            int const role
        )
        const;

    private:

        VariantCollection * variants;
};

/******************************************************************************/

#endif /* VARIANT_LIST_MODEL_H */
