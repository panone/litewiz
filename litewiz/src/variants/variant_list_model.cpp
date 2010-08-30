/*******************************************************************************
*******************************************************************************/

#include <QFont>
#include "session.h"
#include "context_menu_info.h"
#include "variant.h"
#include "variant_collection.h"
#include "file_cluster_list_model.h"
#include "variant_list_model.h"

/*******************************************************************************
*******************************************************************************/
VariantListModel::VariantListModel
(
    Session * const session,
    QObject * const parent
) :
    FileClusterListModel( session->getVariants(), parent )
{
    variants = session->getVariants();

    connect( session, SIGNAL( classificationChanged() ), this, SLOT( update() ) );
}

/*******************************************************************************
*******************************************************************************/
void VariantListModel::initContextMenu
(
    ContextMenuInfo * const menuInfo
)
{
    FileClusterListModel::initContextMenu( menuInfo );

    if ( menuInfo->getSelection().count() == 1 )
    {
        if ( variants->getVariant( menuInfo->getSelection().first() )->isReference() )
        {
            menuInfo->addMenuEntry( ContextMenuInfo::ReferenceChecked );
        }
        else
        {
            menuInfo->addMenuEntry( ContextMenuInfo::ReferenceUnchecked );
        }
    }
}


/*******************************************************************************
*******************************************************************************/
void VariantListModel::toggleReference
(
    QModelIndex const & index
)
{
    if ( index.isValid() )
    {
        variants->toggleReference( index.row() );

        emit dataChanged( index, index );
    }
}

/*******************************************************************************
*******************************************************************************/
QVariant VariantListModel::getData
(
    int const index,
    int const role
)
    const
{
    QVariant result = FileClusterListModel::getData( index, role );

    switch ( role )
    {
        case Qt::FontRole:
            if ( variants->getVariant( index )->isReference() )
            {
                QFont font;

                font.setBold( true );

                result = font;
            }
            break;
    }

    return result;
}

/******************************************************************************/
