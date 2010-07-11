/*******************************************************************************
*******************************************************************************/

#include <QAbstractItemModel>
#include <QMap>
#include <QString>
#include "file.h"
#include "file_collection.h"
#include "file_tree_item.h"
#include "file_tree_model.h"

/*******************************************************************************
*******************************************************************************/
FileTreeModel::FileTreeModel
(
    FileCollection * const files,
    QObject        * const parent
) :
    QAbstractItemModel( parent ),
    files( files )
{
    foreach ( File const & file, *files )
    {
        QString path = file.getPath();

        if ( !items.contains( path ) )
        {
            items[ path ] = new FileTreeItem( path );
        }

        items[ path ]->addSubItem( file );
    }
}

/*******************************************************************************
*******************************************************************************/
FileTreeModel::~FileTreeModel
(
    void
)
{
    qDeleteAll( items );
}

/*******************************************************************************
*******************************************************************************/
int FileTreeModel::rowCount
(
    QModelIndex const & parent
)
    const
{
    int result = 0;

    if ( getItem( parent ) != 0 )
    {
        result = getItem( parent )->getRowCount();
    }
    else
    {
        result = items.count();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
int FileTreeModel::columnCount
(
    QModelIndex const & parent
)
    const
{
    int result = 3;

    if ( getItem( parent ) != 0 )
    {
        result = getItem( parent )->getColumnCount();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QModelIndex FileTreeModel::index
(
    int                 row,
    int                 column,
    QModelIndex const & parent
)
    const
{
    FileTreeItem * parentItem = getItem( parent );
    FileTreeItem * item       = 0;

    if ( parentItem != 0 )
    {
        if ( ( row >= 0 ) && ( row < parentItem->getRowCount() ) )
        {
            item = parentItem->getSubItem( row );
        }
    }
    else
    {
        if ( ( row >= 0 ) && ( row < items.count() ) )
        {
            item = items[ items.keys().at( row ) ];
        }
    }

    QModelIndex result;

    if ( item != 0 )
    {
        result = createIndex( row, column, item );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QModelIndex FileTreeModel::parent
(
    QModelIndex const & index
)
    const
{
    QModelIndex    result;
    FileTreeItem * item = getItem( index );

    if ( ( item != 0 ) && ( item->getParent() != 0 ) )
    {
        result = createIndex( item->getRow(), 0, item->getParent() );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeModel::data
(
    QModelIndex const & index,
    int                 role
)
    const
{
    QVariant result;

    if ( getItem( index ) != 0 )
    {
        result = getItem( index )->getData( index.column(), role );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
Qt::ItemFlags FileTreeModel::flags
(
    QModelIndex const & index
)
    const
{
    Qt::ItemFlags result = 0;

    if ( index.isValid() )
    {
        result = Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeModel::headerData
(
    int               section,
    Qt::Orientation   orientation,
    int               role
)
    const
{
    static QString header[ 3 ] =
    {
        tr( "Name" ),
        tr( "Item" ),
        tr( "Variant" )
    };

    QVariant result;

    if ( ( section >= 0 ) && ( section < 3 ) && ( orientation == Qt::Horizontal ) && ( role == Qt::DisplayRole ) )
    {
        result = header[ section ];
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeModel::getItem
(
    QModelIndex const & index
)
    const
{
    FileTreeItem * result = 0;

    if ( index.isValid() )
    {
        result = static_cast< FileTreeItem * >( index.internalPointer() );
    }

    return result;
}

/******************************************************************************/
