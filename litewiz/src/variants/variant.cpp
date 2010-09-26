/*******************************************************************************
*******************************************************************************/

#include <QApplication>
#include "file_cluster.h"
#include "variant.h"

/*******************************************************************************
*******************************************************************************/
Variant::Variant
(
    QString                const & name,
    QString                const & stem,
    QList< FileCluster * > const & collection
) :
    FileCluster( name, stem, collection )
{
    if ( name[ 0 ] == '-' )
    {
        if ( name == "-ref-" )
        {
            this->name = QApplication::tr( "Reference" );
        }
        else
        {
            this->name = QApplication::tr( "Variant %1" ).arg( name[ 1 ] );
        }
    }

    reference = false;
}

/*******************************************************************************
*******************************************************************************/
void Variant::setReference
(
    bool const reference
)
{
    this->reference = reference;
}

/*******************************************************************************
*******************************************************************************/
bool Variant::isReference
(
    void
)
    const
{
    return reference;
}

/******************************************************************************/
