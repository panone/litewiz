/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QString>
#include <QVariant>
#include "file.h"
#include "file_tree_item.h"

/*******************************************************************************
*******************************************************************************/
FileTreeItem::FileTreeItem
(
    QString const & name
)
{
    directory = true;
    fileName  = name;
    parent    = 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::FileTreeItem
(
    File const & file
)
{
    directory   = false;
    fileName    = file.getName();
    itemName    = file.getItem();
    variantName = file.getVariant();
    parent      = 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::~FileTreeItem
(
    void
)
{
    qDeleteAll( children );
}

/*******************************************************************************
*******************************************************************************/
void FileTreeItem::addSubItem
(
    File const & file
)
{
    FileTreeItem * item = new FileTreeItem( file );

    item->parent = this;

    children.append( item );
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getRowCount
(
    void
)
    const
{
    return children.count();
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getColumnCount
(
    void
)
    const
{
    return directory ? 1 : 3;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getData
(
    int const column,
    int const role
)
    const
{
    QVariant result;

    if ( role == Qt::DisplayRole )
    {
        if ( column == 0 )
        {
            result = fileName;
        }
        else
        {
            if ( !directory )
            {
                switch ( column )
                {
                    case 1:
                        result = itemName;
                        break;

                    case 2:
                        result = variantName;
                        break;
                }
            }
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::getParent
(
    void
)
    const
{
    return parent;
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getRow
(
    void
)
    const
{
    int result = 0;

    if ( parent != 0 )
    {
        result = parent->children.indexOf( const_cast< FileTreeItem * >( this ) );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::getSubItem
(
    int const row
)
    const
{
    return children.at( row );
}

/******************************************************************************/
