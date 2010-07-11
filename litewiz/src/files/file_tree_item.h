/*******************************************************************************
*******************************************************************************/

#ifndef FILE_TREE_ITEM_H
#define FILE_TREE_ITEM_H

/******************************************************************************/

#include <QList>
#include <QString>
#include <QVariant>

/******************************************************************************/

class File;

/*******************************************************************************
*******************************************************************************/
class FileTreeItem
{
    public:

        explicit FileTreeItem
        (
            QString const & name
        );

        explicit FileTreeItem
        (
            File const & file
        );

        ~FileTreeItem
        (
            void
        );

    public:

        FileTreeItem * addSubItem
        (
            QString const & name
        );

        FileTreeItem * addSubItem
        (
            File const & file
        );

        int getRowCount
        (
            void
        )
        const;

        int getColumnCount
        (
            void
        )
        const;

        QVariant getData
        (
            int const column,
            int const role
        )
        const;

        FileTreeItem * getParent
        (
            void
        )
        const;

        int getRow
        (
            void
        )
        const;

        FileTreeItem * findSubItem
        (
            QString const & name
        )
        const;

        FileTreeItem * getSubItem
        (
            int const row
        )
        const;

    private:

        bool                      directory;

        QString                   fileName;
        QString                   itemName;
        QString                   variantName;

        FileTreeItem            * parent;

        QList< FileTreeItem * >   children;
};

/******************************************************************************/

#endif /* FILE_TREE_ITEM_H */
