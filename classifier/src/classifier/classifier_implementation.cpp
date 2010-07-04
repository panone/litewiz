/*******************************************************************************
*******************************************************************************/

#include <QObject>
#include <QStringList>
#include <QVariant>
#include "extractor.h"
#include "clusters_extractor.h"
#include "classifier_implementation.h"

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::ClassifierImplementation
(
    QStringList const &       fileNames,
    QObject           * const parent
) :
    QObject( parent ),
    fileNames( fileNames )
{
    extractors[ Clusters ] = new ClustersExtractor( this );
}

/*******************************************************************************
*******************************************************************************/
ClassifierImplementation::~ClassifierImplementation
(
    void
)
{
    foreach ( Extractor * extractor, extractors )
    {
        delete extractor;
    }
}

/*******************************************************************************
*******************************************************************************/
int ClassifierImplementation::classify
(
    void
)
{
    return 42;
}

/*******************************************************************************
*******************************************************************************/
QVariantList ClassifierImplementation::getData
(
    DataIdentifier const identifier
)
{
    QVariantList result;

    if ( identifier == FileNames )
    {
        foreach ( QString fileName, fileNames )
        {
            result.append( fileName );
        }
    }
    else
    {
        //result = extractors[ identifier ]->getData();
    }

    return result;
}

/******************************************************************************/
