/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QAbstractListModel>
#include <QPalette>
#include "utility.h"
#include "session.h"
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
                result = variant->getName();
                break;

            case Qt::ForegroundRole:
                if ( variant->isExcluded() )
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
    QIntList const &       selection,
    bool           * const exclude,
    bool           * const include
)
{
    *exclude = false;
    *include = false;

    foreach ( int index, selection )
    {
        if ( session->getVariants().getVariant( index )->isExcluded() )
        {
            *include = true;
        }
        else
        {
            *exclude = true;
        }
    }
}

/******************************************************************************/
