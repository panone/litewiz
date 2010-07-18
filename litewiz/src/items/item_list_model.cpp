/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QAbstractListModel>
#include <QPalette>
#include "session.h"
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
void ItemListModel::update
(
    void
)
{
    reset();
}

/******************************************************************************/