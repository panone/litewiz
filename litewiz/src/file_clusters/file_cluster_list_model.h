/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_LIST_MODEL_H
#define FILE_CLUSTER_LIST_MODEL_H

/******************************************************************************/

#include <QAbstractListModel>

/******************************************************************************/

class ContextMenuInfo;
class FileClusterCollection;

/*******************************************************************************
*******************************************************************************/
class FileClusterListModel : public QAbstractListModel
{
    Q_OBJECT

    protected:

        FileClusterListModel
        (
            FileClusterCollection * const clusters,
            QObject               * const parent = 0
        );

    public slots:

        void update
        (
            void
        );

        void initContextMenu
        (
            ContextMenuInfo * const menuInfo
        );

    public:

        virtual int rowCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        virtual QVariant data
        (
            QModelIndex const & index,
            int                 role
        )
        const;

        virtual bool setData
        (
            QModelIndex const & index,
            QVariant    const & value,
            int                 role = Qt::EditRole
        );

        virtual Qt::ItemFlags flags
        (
            QModelIndex const & index
        )
        const;

        virtual Qt::DropActions supportedDropActions
        (
            void
        )
        const;

        virtual QStringList mimeTypes
        (
            void
        )
        const;

        virtual QMimeData * mimeData
        (
            QModelIndexList const & indexes
        )
        const;

        virtual bool dropMimeData
        (
            QMimeData      const * data,
            Qt::DropAction         action,
            int                    row,
            int                    column,
            QModelIndex    const & parent
        );

    protected:

        virtual QVariant getData
        (
            int const index,
            int const role
        )
        const;

    protected:

        FileClusterCollection * clusters;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_LIST_MODEL_H */
