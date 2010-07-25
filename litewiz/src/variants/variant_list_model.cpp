/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QAbstractListModel>
#include <QFont>
#include <QPalette>
#include "utility.h"
#include "session.h"
#include "context_menu_info.h"
#include "variant.h"
#include "variant_collection.h"
#include "variant_list_model.h"

/*******************************************************************************
*******************************************************************************/
VariantListModel::VariantListModel
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
int VariantListModel::rowCount
(
    QModelIndex const & parent
)
    const
{
    return session->getVariants().getCount();
}

/*******************************************************************************
*******************************************************************************/
QVariant VariantListModel::data
(
    QModelIndex const & index,
    int                 role
)
    const
{
    QVariant result;

    if ( index.isValid() )
    {
        Variant const * variant = session->getVariants().getVariant( index.row() );

        switch ( role )
        {
            case Qt::DisplayRole:
            case Qt::EditRole:
                result = variant->getName();
                break;

            case Qt::ForegroundRole:
                if ( variant->isExcluded() )
                {
                    result = QApplication::palette().brush( QPalette::Window );
                }
                break;

            case Qt::FontRole:
                if ( variant->isReference() )
                {
                    QFont font;

                    font.setBold( true );

                    result = font;
                }
                break;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool VariantListModel::setData
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
        session->getVariants().getVariant( index.row() )->setName( name );

        result = true;

        emit dataChanged( index, index );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
Qt::ItemFlags VariantListModel::flags
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
void VariantListModel::update
(
    void
)
{
    reset();
}

/*******************************************************************************
*******************************************************************************/
void VariantListModel::initContextMenu
(
    ContextMenuInfo * const menuInfo
)
{
    menuInfo->clearMenuEntries();

    foreach ( int index, menuInfo->getSelection() )
    {
        if ( session->getVariants().getVariant( index )->isExcluded() )
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Include );
        }
        else
        {
            menuInfo->addMenuEntry( ContextMenuInfo::Exclude );
        }
    }

    if ( menuInfo->getSelection().count() == 1 )
    {
        if ( session->getVariants().getVariant( menuInfo->getSelection().first() )->isReference() )
        {
            menuInfo->addMenuEntry( ContextMenuInfo::ReferenceChecked );
        }
        else
        {
            menuInfo->addMenuEntry( ContextMenuInfo::ReferenceUnchecked );
        }
    }
}

/******************************************************************************/
