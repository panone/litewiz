/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_LIST_VIEW_H
#define ITEM_LIST_VIEW_H

/******************************************************************************/

#include "file_cluster_list_view.h"

/*******************************************************************************
*******************************************************************************/
class ItemListView : public FileClusterListView
{
    Q_OBJECT

    public:

        ItemListView
        (
            QWidget * const parent = 0
        );
};

/******************************************************************************/

#endif /* ITEM_LIST_VIEW_H */
