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
    private:

        static bool naturalCompare
        (
            FileTreeItem * const item1,
            FileTreeItem * const item2
        );

    public:

        explicit FileTreeItem
        (
            QString const & name
        );

        explicit FileTreeItem
        (
            File const * const file
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
            File const * const file
        );

        void sort
        (
            void
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

        QString getName
        (
            void
        );

        QVariant getFileData
        (
            int const role
        )
        const;

        QVariant getItemData
        (
            int const role
        )
        const;

        QVariant getVariantData
        (
            int const role
        )
        const;

        QVariant getDirectoryData
        (
            int const role
        )
        const;

    private:

        QString                         directoryName;

        File                    const * file;

        FileTreeItem                  * parent;

        QList< FileTreeItem * >         children;
};

/******************************************************************************/

#endif /* FILE_TREE_ITEM_H */
