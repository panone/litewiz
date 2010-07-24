/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QString>
#include "classifier_implementation.h"
#include "classifier.h"

/*******************************************************************************
*******************************************************************************/
Classifier::Classifier
(
    void
)
{
    implementation = new ClassifierImplementation();

    items    = 0;
    variants = 0;
}

/*******************************************************************************
*******************************************************************************/
Classifier::~Classifier
(
    void
)
{
    delete implementation;
}

/*******************************************************************************
*******************************************************************************/
void Classifier::classify
(
    QStringList const & fileNames
)
{
    implementation->classify( fileNames );

    for ( variants = 8; variants > 0; variants-- )
    {
        if ( ( fileNames.count() % variants ) == 0 )
        {
            break;
        }
    }

    items = fileNames.count() / variants;
}

/*******************************************************************************
*******************************************************************************/
int Classifier::getDefaultVariance
(
    void
)
{
    return variants; //implementation->getDefaultVariance();
}

/*******************************************************************************
*******************************************************************************/
QList< ItemInfo > Classifier::getItems
(
    int variance
)
{
    QList< ItemInfo > result;

    for ( int i = 0; i < items; i++ )
    {
        ItemInfo info;

        info.name = QString( "item_%1" ).arg( i + 1 );
        info.stem = QString( "item_%1_stem" ).arg( i + 1 );

        for ( int v = 0; v < variants; v++ )
        {
            info.files.append( v * items + i );
        }

        result.append( info );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QList< VariantInfo > Classifier::getVariants
(
    int variance
)
{
    QList< VariantInfo > result;

    for ( int v = 0; v < variants; v++ )
    {
        VariantInfo info;

        info.name = QString( "variant_%1" ).arg( v + 1 );
        info.stem = QString( "variant_%1_stem" ).arg( v + 1 );

        info.reference = ( v == 0 );

        for ( int i = 0; i < items; i++ )
        {
            info.files.append( v * items + i );
        }

        result.append( info );
    }

    return result;
}

/******************************************************************************/
