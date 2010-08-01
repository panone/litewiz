/*******************************************************************************
*******************************************************************************/

#include <QAbstractItemModel>
#include <QMap>
#include <QString>
#include "file.h"
#include "file_collection.h"
#include "session.h"
#include "file_tree_item.h"
#include "file_tree_model.h"

/*******************************************************************************
*******************************************************************************/
FileTreeModel::FileTreeModel
(
    Session * const session,
    QObject * const parent
) :
    QAbstractItemModel( parent ),
    session( session )
{
    root = new FileTreeItem( "root" );

    connect( session, SIGNAL( fileCollectionUpdated() ), this, SLOT( update() ) );
    connect( session, SIGNAL( classified() ), this, SLOT( update() ) );

    update();
}

/*******************************************************************************
*******************************************************************************/
FileTreeModel::~FileTreeModel
(
    void
)
{
    delete root;
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

    if ( parent.column() <= 0 )
    {
        if ( getItem( parent ) != 0 )
        {
            result = getItem( parent )->getRowCount();
        }
        else
        {
            result = root->getRowCount();
        }
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

    if ( parentItem == 0 )
    {
        parentItem = root;
    }

    if ( ( row >= 0 ) && ( row < parentItem->getRowCount() ) )
    {
        item = parentItem->getSubItem( row );
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

    if ( ( item != 0 ) && ( item->getParent() != root ) )
    {
        result = createIndex( item->getParent()->getRow(), 0, item->getParent() );
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

/*******************************************************************************
*******************************************************************************/
void FileTreeModel::update
(
    void
)
{
    delete root;

    root = new FileTreeItem( "root" );

    foreach ( File const * file, session->getFiles()->getAllFiles() )
    {
        FileTreeItem * directory = root->findSubItem( file->getPath() );

        if ( directory == 0 )
        {
            directory = root->addSubItem( file->getPath() );
        }

        directory->addSubItem( file );
    }

    root->sort();

    reset();
}

/******************************************************************************/
