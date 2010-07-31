/*******************************************************************************
*******************************************************************************/

#include <QMimeData>
#include <QtGui/QApplication>
#include <QAbstractListModel>
#include <QPalette>
#include "context_menu_info.h"
#include "file_cluster.h"
#include "file_cluster_collection.h"
#include "file_cluster_list_model.h"

/*******************************************************************************
*******************************************************************************/
FileClusterListModel::FileClusterListModel
(
    FileClusterCollection * const clusters,
    QObject               * const parent
) :
    QAbstractListModel( parent ),
    clusters( clusters )
{
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListModel::update
(
    void
)
{
    reset();
}

/*******************************************************************************
*******************************************************************************/
void FileClusterListModel::initContextMenu
(
    ContextMenuInfo * const menuInfo
)
{
    menuInfo->clearMenuEntries();

    foreach ( int index, menuInfo->getSelection() )
    {
        if ( clusters->getCluster( index )->isExcluded() )
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Include );
        }
        else
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Exclude );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
int FileClusterListModel::rowCount
(
    QModelIndex const & parent
)
    const
{
    return clusters->getCount();
}

/*******************************************************************************
*******************************************************************************/
QVariant FileClusterListModel::data
(
    QModelIndex const & index,
    int                 role
)
    const
{
    QVariant result;

    if ( index.isValid() )
    {
        result = getData( index.row(), role );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool FileClusterListModel::setData
(
    QModelIndex const & index,
    QVariant    const & value,
    int                 role
)
{
    bool      result = false;
    QString   name   = value.toString();

    if ( index.isValid() && !name.isEmpty() && ( role == Qt::EditRole ) )
    {
        clusters->getCluster( index.row() )->setName( name );

        result = true;

        emit dataChanged( index, index );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
Qt::ItemFlags FileClusterListModel::flags
(
    QModelIndex const & index
)
    const
{
    Qt::ItemFlags result = QAbstractListModel::flags( index );

    if ( index.isValid() )
    {
        result |= Qt::ItemIsEditable | Qt::ItemIsDragEnabled;
    }
    else
    {
        result |= Qt::ItemIsDropEnabled;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
Qt::DropActions FileClusterListModel::supportedDropActions
(
    void
)
    const
{
    return Qt::MoveAction;
}

/*******************************************************************************
*******************************************************************************/
QStringList FileClusterListModel::mimeTypes
(
    void
)
    const
{
    QStringList result;

    result.append( "application/x-litewizindexlist" );

    return result;
}

/*******************************************************************************
*******************************************************************************/
QMimeData * FileClusterListModel::mimeData
(
    QModelIndexList const & indexes
)
    const
{
    QMimeData * result = 0;

    if ( indexes.count() > 0 )
    {
        QByteArray    data;
        QDataStream   stream( &data, QIODevice::WriteOnly );

        foreach ( QModelIndex const & index, indexes )
        {
            stream << index.row();
        }

        result = new QMimeData();

        result->setData( mimeTypes().first(), data );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool FileClusterListModel::dropMimeData
(
    QMimeData      const * data,
    Qt::DropAction         action,
    int                    row,
    int                    column,
    QModelIndex    const & parent
)
{
    bool result = false;

    if ( ( data != 0 ) && ( action == Qt::MoveAction ) && data->hasFormat( mimeTypes().first() ) )
    {
        int target = row;

        if ( ( target == -1 ) || ( target > clusters->getCount() ) )
        {
            target = clusters->getCount();
        }

        QByteArray    bytes = data->data( mimeTypes().first() );
        QDataStream   stream( &bytes, QIODevice::ReadOnly );
        QIntList      selection;

        while ( !stream.atEnd() )
        {
            int index;

            stream >> index;

            selection.append( index );
        }

        qSort( selection );

        clusters->move( target, selection );

        result = true;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileClusterListModel::getData
(
    int const index,
    int const role
)
    const
{
    FileCluster const * cluster = clusters->getCluster( index );
    QVariant            result;

    switch ( role )
    {
        case Qt::DisplayRole:
        case Qt::EditRole:
            result = cluster->getName();
            break;

        case Qt::ForegroundRole:
            if ( cluster->isExcluded() )
            {
                result = QApplication::palette().brush( QPalette::Window );
            }
            break;
    }

    return result;
}

/******************************************************************************/
