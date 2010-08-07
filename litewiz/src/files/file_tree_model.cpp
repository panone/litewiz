/*******************************************************************************
*******************************************************************************/

#include <QAbstractItemModel>
#include <QMap>
#include <QMimeData>
#include <QString>
#include <QStringList>
#include <QUrl>
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
    FileTreeItem * oldRoot = root;

    root = new FileTreeItem( "root" );

    foreach ( File const * file, session->getFiles()->getAllFiles() )
    {
        FileTreeItem * directory = root->findSubItem( file->getPath() );

        if ( directory == 0 )
        {
            directory = root->addSubItem( file->getPath() );

            FileTreeItem * oldDirectory = oldRoot->findSubItem( file->getPath() );

            if ( oldDirectory != 0 )
            {
                directory->expand( oldDirectory->isExpanded() );
            }
        }

        directory->addSubItem( file );
    }

    delete oldRoot;

    root->sort();

    reset();
}

/*******************************************************************************
*******************************************************************************/
void FileTreeModel::collapse
(
    QModelIndex const & index
)
{
    if ( getItem( index ) != 0 )
    {
        getItem( index )->expand( false );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileTreeModel::expand
(
    QModelIndex const & index
)
{
    if ( getItem( index ) != 0 )
    {
        getItem( index )->expand( true );
    }
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
    return QAbstractItemModel::flags( index ) | Qt::ItemIsDropEnabled;
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
Qt::DropActions FileTreeModel::supportedDropActions
(
    void
)
    const
{
    return Qt::CopyAction;
}

/*******************************************************************************
*******************************************************************************/
QStringList FileTreeModel::mimeTypes
(
    void
)
    const
{
    QStringList result;

    result.append( "text/uri-list" );

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool FileTreeModel::dropMimeData
(
    QMimeData      const * data,
    Qt::DropAction         action,
    int                    row,
    int                    column,
    QModelIndex    const & parent
)
{
    bool result = false;

    if ( ( data != 0 ) && ( action == Qt::CopyAction ) && data->hasUrls() )
    {
        session->addUrls( data->urls() );

        result = true;
    }

    return result;
}

/******************************************************************************/
