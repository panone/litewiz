/*******************************************************************************
*******************************************************************************/

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
        result |= Qt::ItemIsEditable;
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
