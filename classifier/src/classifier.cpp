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

    variance.clear();

    for ( int variants = 8; variants > 0; variants-- )
    {
        if ( ( fileNames.count() % variants ) == 0 )
        {
            variance.append( variants );
        }
    }

    qSort( variance );
}

/*******************************************************************************
*******************************************************************************/
QList< int > Classifier::getPossibleVariance
(
    void
)
{
    return variance;
}

/*******************************************************************************
*******************************************************************************/
int Classifier::getDefaultVariance
(
    void
)
{
    return variance.last(); //implementation->getDefaultVariance();
}

/*******************************************************************************
*******************************************************************************/
ClassificationInfo Classifier::getClassification
(
    int variance
)
{
    ClassificationInfo result;

    int items = files / variance;

    for ( int i = 0; i < items; i++ )
    {
        ItemInfo info;

        info.name = QString( "item_%1" ).arg( i + 1 );
        info.stem = QString( "item_%1_stem" ).arg( i + 1 );

        for ( int v = 0; v < variance; v++ )
        {
            info.files.append( v * items + i );
        }

        result.items.append( info );
    }

    for ( int v = 0; v < variance; v++ )
    {
        VariantInfo info;

        info.name = QString( "variant_%1" ).arg( v + 1 );
        info.stem = QString( "variant_%1_stem" ).arg( v + 1 );

        info.reference = ( v == 0 );

        for ( int i = 0; i < items; i++ )
        {
            info.files.append( v * items + i );
        }

        result.variants.append( info );
    }

    return result;
}

/******************************************************************************/
