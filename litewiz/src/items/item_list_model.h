/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_LIST_MODEL_H
#define ITEM_LIST_MODEL_H

/******************************************************************************/

#include <QAbstractListModel>
#include "utility.h"

/******************************************************************************/

class ContextMenuInfo;
class Session;

/*******************************************************************************
*******************************************************************************/
class ItemListModel : public QAbstractListModel
{
    Q_OBJECT

    public:

        ItemListModel
        (
            Session * const session,
            QObject * const parent = 0
        );

    public:

        int rowCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        QVariant data
        (
            QModelIndex const & index,
            int                 role
        )
        const;

    public slots:

        void update
        (
            void
        );

        void initContextMenu
        (
            ContextMenuInfo * const menuInfo
        );

    private:

        Session * session;
};

/******************************************************************************/

#endif /* ITEM_LIST_MODEL_H */
