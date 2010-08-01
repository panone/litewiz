/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_LIST_MODEL_H
#define FILE_CLUSTER_LIST_MODEL_H

/******************************************************************************/

#include <QAbstractListModel>
#include "utility.h"

/******************************************************************************/

class QItemSelection;
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

    protected:

        QMimeData * encodeMimeData
        (
            QModelIndexList const & indexes
        )
        const;

        QIntList decodeMimeData
        (
            QMimeData const * const indexes
        );

        void updateSelection
        (
            int const startRow,
            int const rows
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

        void exclude
        (
            QIntList const &       selection,
            bool             const exclude
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

    signals:

        void selectionMoved
        (
            QItemSelection const & selection
        );

    protected:

        FileClusterCollection * clusters;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_LIST_MODEL_H */
