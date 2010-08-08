/*******************************************************************************
*******************************************************************************/

#ifndef FILE_TREE_MODEL_H
#define FILE_TREE_MODEL_H

/******************************************************************************/

#include <QAbstractItemModel>
#include <QMap>

/******************************************************************************/

class Session;
class FileTreeItem;

/*******************************************************************************
*******************************************************************************/
class FileTreeModel : public QAbstractItemModel
{
    Q_OBJECT

    public:

        enum ItemDataRole
        {
            ExpandedRole = 33
        };

    public:

        FileTreeModel
        (
            Session * const session,
            QObject * const parent = 0
        );

        ~FileTreeModel
        (
            void
        );

    private:

        FileTreeItem * getItem
        (
            QModelIndex const & index
        )
        const;

    public slots:

        void update
        (
            void
        );

        void collapse
        (
            QModelIndex const & index
        );

        void expand
        (
            QModelIndex const & index
        );

        void remove
        (
            QModelIndexList const & indexes
        );

    public:

        virtual int rowCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        virtual int columnCount
        (
            QModelIndex const & parent = QModelIndex()
        )
        const;

        virtual QModelIndex index
        (
            int                 row,
            int                 column,
            QModelIndex const & parent = QModelIndex()
        )
        const;

        virtual QModelIndex parent
        (
            QModelIndex const & index
        )
        const;

        virtual QVariant data
        (
            QModelIndex const & index,
            int                 role
        )
        const;

        virtual Qt::ItemFlags flags
        (
            QModelIndex const & index
        )
        const;

        virtual QVariant headerData
        (
            int               section,
            Qt::Orientation   orientation,
            int               role = Qt::DisplayRole
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

        virtual bool dropMimeData
        (
            QMimeData      const * data,
            Qt::DropAction         action,
            int                    row,
            int                    column,
            QModelIndex    const & parent
        );

    private:

        Session      * session;
        FileTreeItem * root;
};

/******************************************************************************/

#endif /* FILE_TREE_MODEL_H */
