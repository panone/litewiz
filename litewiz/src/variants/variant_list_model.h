/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_LIST_MODEL_H
#define VARIANT_LIST_MODEL_H

/******************************************************************************/

#include <QAbstractListModel>
#include "utility.h"

/******************************************************************************/

class ContextMenuInfo;
class Session;

/*******************************************************************************
*******************************************************************************/
class VariantListModel : public QAbstractListModel
{
    Q_OBJECT

    public:

        VariantListModel
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

        bool setData
        (
            QModelIndex const & index,
            QVariant    const & value,
            int                 role = Qt::EditRole
        );

        Qt::ItemFlags flags
        (
            QModelIndex const & index
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

#endif /* VARIANT_LIST_MODEL_H */
