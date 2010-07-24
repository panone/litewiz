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
    directoryName = name;
    file          = 0;
    parent        = 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::FileTreeItem
(
    File const * const file
) :
    file( file )
{
    parent = 0;
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
FileTreeItem * FileTreeItem::addSubItem
(
    QString const & name
)
{
    FileTreeItem * item = new FileTreeItem( name );

    item->parent = this;

    children.append( item );

    return item;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::addSubItem
(
    File const * const file
)
{
    FileTreeItem * item = new FileTreeItem( file );

    item->parent = this;

    children.append( item );

    return item;
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
    return 3;
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
        if ( file != 0 )
        {
            switch ( column )
            {
                case 0:
                    result = file->getName();
                    break;

                case 1:
                    result = file->getItemName();
                    break;

                case 2:
                    result = file->getVariantName();
                    break;
            }
        }
        else
        {
            result = directoryName;
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
FileTreeItem * FileTreeItem::findSubItem
(
    QString const & name
)
    const
{
    FileTreeItem * result = 0;

    foreach ( FileTreeItem * item, children )
    {
        if ( item->getName() == name )
        {
            result = item;
            break;
        }
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

/*******************************************************************************
*******************************************************************************/
QString FileTreeItem::getName
(
    void
)
{
    QString result;

    if ( file != 0 )
    {
        result = file->getName();
    }
    else
    {
        result = directoryName;
    }

    return result;
}

/******************************************************************************/
