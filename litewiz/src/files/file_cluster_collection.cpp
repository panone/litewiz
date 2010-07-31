/*******************************************************************************
*******************************************************************************/

#include <QList>
#include "classifier.h"
#include "utility.h"
#include "file_cluster.h"
#include "file_cluster_collection.h"

/*******************************************************************************
*******************************************************************************/
FileClusterCollection::~FileClusterCollection
(
    void
)
{
    qDeleteAll( clusters );
}

/*******************************************************************************
*******************************************************************************/
int FileClusterCollection::getCount
(
    void
)
    const
{
    return clusters.count();
}

/*******************************************************************************
*******************************************************************************/
void FileClusterCollection::clear
(
    void
)
{
    qDeleteAll( clusters );

    clusters.clear();
}

/*******************************************************************************
*******************************************************************************/
void FileClusterCollection::exclude
(
    QIntList const &       selection,
    bool             const exclude
)
{
    foreach ( int index, selection )
    {
        if ( ( index >= 0 ) && ( index < clusters.count() ) )
        {
            clusters[ index ]->exclude( exclude );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void FileClusterCollection::move
(
    int              const target,
    QIntList const &       selection
)
{
    QList< FileCluster * > reordered;
    int                    reorderedTarget = -1;

    for ( int i = 0; i < clusters.count(); i++ )
    {
        if ( i == target )
        {
            reorderedTarget = reordered.count();
        }

        if ( selection.indexOf( i ) == -1 )
        {
            reordered.append( clusters[ i ] );
        }
    }

    if ( reorderedTarget == -1 )
    {
        reorderedTarget = reordered.count();
    }

    for ( int i = 0; i < selection.count(); i++ )
    {
        reordered.insert( reorderedTarget + i, clusters[ selection[ i ] ] );
    }

    clusters = reordered;
}

/******************************************************************************/
