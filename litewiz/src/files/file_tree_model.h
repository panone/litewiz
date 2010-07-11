/*******************************************************************************
*******************************************************************************/

#ifndef FILE_TREE_MODEL_H
#define FILE_TREE_MODEL_H

/******************************************************************************/

#include <QAbstractItemModel>
#include <QMap>

/******************************************************************************/

class FileCollection;
class FileTreeItem;

/*******************************************************************************
*******************************************************************************/
class FileTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    public:

        FileTreeModel
        (
            FileCollection * const files,
            QObject        * const parent = 0
        );

        ~FileTreeModel
        (
            void
        );

    public:

        int rowCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        int columnCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        QModelIndex index
        (
            int                 row,
            int                 column,
            QModelIndex const & parent = QModelIndex()
        )
        const;

        QModelIndex parent
        (
            QModelIndex const & index
        )
        const;

        QVariant data
        (
            QModelIndex const & index,
            int                 role
        )
        const;

        Qt::ItemFlags flags
        (
            QModelIndex const & index
        )
        const;

        QVariant headerData
        (
            int               section,
            Qt::Orientation   orientation,
            int               role = Qt::DisplayRole
        )
        const;

    private:

        FileTreeItem * getItem
        (
            QModelIndex const & index
        )
        const;

    private:

        FileCollection * files;
        FileTreeItem   * root;
};

/******************************************************************************/

#endif /* FILE_TREE_MODEL_H */
