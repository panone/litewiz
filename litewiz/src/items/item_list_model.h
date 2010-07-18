/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_LIST_MODEL_H
#define ITEM_LIST_MODEL_H

/******************************************************************************/

#include <QAbstractListModel>
#include "utility.h"

/******************************************************************************/

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
            QIntList const &       selection,
            bool           * const exclude,
            bool           * const include
        );

    private:

        Session * session;
};

/******************************************************************************/

#endif /* ITEM_LIST_MODEL_H */
