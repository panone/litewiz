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

    files = 0;
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

    files = fileNames.count();
}

/*******************************************************************************
*******************************************************************************/
int Classifier::getDefaultVariance
(
    void
)
{
    return 1; //implementation->getDefaultVariance();
}

/*******************************************************************************
*******************************************************************************/
QList< ItemInfo > Classifier::getItems
(
    int variance
)
{
    QList< ItemInfo > result;

    for ( int f = 0; f < files; f++ )
    {
        ItemInfo info;

        info.name = QString( "item_%1" ).arg( f + 1 );
        info.stem = QString( "item_%1_stem" ).arg( f + 1 );

        info.files.append( f );

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
    VariantInfo info;

    info.name = "variant_1";
    info.stem = "variant_1_stem";

    for ( int f = 0; f < files; f++ )
    {
        info.files.append( f );
    }

    QList< VariantInfo > result;

    result.append( info );

    return result;
}

/******************************************************************************/
