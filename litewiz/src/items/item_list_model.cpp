/*******************************************************************************
*******************************************************************************/

#include <QMimeData>
#include <QtGui/QApplication>
#include <QAbstractListModel>
#include <QPalette>
#include "utility.h"
#include "session.h"
#include "context_menu_info.h"
#include "item.h"
#include "item_collection.h"
#include "item_list_model.h"

/*******************************************************************************
*******************************************************************************/
ItemListModel::ItemListModel
(
    Session * const session,
    QObject * const parent
) :
    QAbstractListModel( parent ),
    session( session )
{
    connect( session, SIGNAL( classified() ), this, SLOT( update() ) );
}

/*******************************************************************************
*******************************************************************************/
int ItemListModel::rowCount
(
    QModelIndex const & parent
)
    const
{
    return session->getItems().getCount();
}

/*******************************************************************************
*******************************************************************************/
QVariant ItemListModel::data
(
    QModelIndex const & index,
    int                 role
)
    const
{
    QVariant result;

    if ( index.isValid() )
    {
        Item const * item = session->getItems().getItem( index.row() );

        switch ( role )
        {
            case Qt::DisplayRole:
            case Qt::EditRole:
                result = item->getName();
                break;

            case Qt::ForegroundRole:
                if ( item->isExcluded() )
                {
                    result = QApplication::palette().brush( QPalette::Window );
                }
                break;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool ItemListModel::setData
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
        session->getItems().getItem( index.row() )->setName( name );

        result = true;

        emit dataChanged( index, index );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
Qt::ItemFlags ItemListModel::flags
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
Qt::DropActions ItemListModel::supportedDropActions
(
    void
)
    const
{
    //return Qt::CopyAction | Qt::MoveAction;
    return Qt::MoveAction;
}

/*******************************************************************************
*******************************************************************************/
QStringList ItemListModel::mimeTypes
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
QMimeData * ItemListModel::mimeData
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
bool ItemListModel::dropMimeData
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

        if ( ( target == -1 ) || ( target > session->getItems().getCount() ) )
        {
            target = session->getItems().getCount();
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

        session->getItems().move( target, selection );

        result = true;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ItemListModel::update
(
    void
)
{
    reset();
}

/*******************************************************************************
*******************************************************************************/
void ItemListModel::initContextMenu
(
    ContextMenuInfo * const menuInfo
)
{
    menuInfo->clearMenuEntries();

    foreach ( int index, menuInfo->getSelection() )
    {
        if ( session->getItems().getItem( index )->isExcluded() )
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Include );
        }
        else
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Exclude );
        }
    }
}

/******************************************************************************/
