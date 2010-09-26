/*******************************************************************************
*******************************************************************************/

#include <QFileInfo>
#include <QList>
#include <QMap>
#include <QSet>
#include <QStringList>
#include "utility.h"
#include "classifier.h"
#include "classifier_implementation.h"

/******************************************************************************/

#define ARRAY_LENGTH( a )               static_cast< int >( sizeof( a ) / sizeof( a[ 0 ] ) )

#define FILE_NAME_SEPARATORS            "_-. |"

#define CLASSIFIER_TUNING

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::classify
(
    QStringList const & fileNames
)
{
    initializeFileDescriptions( fileNames );
    initializeClusters();

    QIntFloatMap   varianceProbability  = getVarianceProbablity();
    QIntMap        clusterSizeCount     = getClusterSizeCount();
    QIntSet        unmatchedClusterSize = getUnmatchedClusterSize();
    StemInfoList   stemClusterInfo      = getStemClusterInfo();

    initializeVariance( varianceProbability );
    detectPopularClusterSizes1();
    detectPopularClusterSizes2( clusterSizeCount );
    detectClusterSizeStep( clusterSizeCount );
    detectUniqueItemClusterSize( unmatchedClusterSize );
    detectUnmatchedClusterSize( unmatchedClusterSize );
    detectSingleItem1( unmatchedClusterSize );
    detectItemClusterSize( stemClusterInfo );
    detectSingleItem2( stemClusterInfo );

    applyVarianceProbability( varianceProbability );
    validateVariance();
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::getPossibleVariance
(
    void
)
{
    QIntList result;

    foreach ( int v, variance.keys() )
    {
        if ( variance[ v ] > 0.0f )
        {
            result.append( v );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
int ClassifierImplementation::getDefaultVariance
(
    void
)
{
    float   maxProbability = 0.0f;
    int     result         = 0;

    foreach ( int v, variance.keys() )
    {
        if ( maxProbability < variance[ v ] )
        {
            maxProbability = variance[ v ];
            result         = v;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
ClassificationInfo ClassifierImplementation::getClassification
(
    int const variance
)
{
    QIntList            splitIndices = getSplitIndices( variance );
    QStringIntListMap   items;
    QStringIntListMap   variants;

    for ( int i = 0; i < fileDescriptions.count(); i++ )
    {
        QString description = fileDescriptions[ i ];

        items[ description.left( splitIndices[ i ] ) ].append( i );
        variants[ description.mid( splitIndices[ i ] ) ].append( i );
    }

    QStringList   itemStems    = items.keys();
    QStringList   variantStems = variants.keys();

    //TODO: SortItems( itemStems );
    //TODO: SortVariants( variantStems );

    QStringMap   itemNames    = getItemNames( itemStems );
    QStringMap   variantNames = getVariantNames( variantStems );

    ClassificationInfo result;

    foreach ( QString const & stem, items.keys() )
    {
        ItemInfo info;

        info.name  = itemNames[ stem ];
        info.stem  = stem;
        info.files = items[ stem ];

        result.items.append( info );
    }

    foreach ( QString const & stem, variants.keys() )
    {
        VariantInfo info;

        info.name  = variantNames[ stem ];
        info.stem  = stem;
        info.files = variants[ stem ];

        result.variants.append( info );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::initializeFileDescriptions
(
    QStringList const & fileNames
)
{
    fileDescriptions.clear();

    QStringListEx directories;

    foreach ( QString const & fileName, fileNames )
    {
        QFileInfo fileInfo( fileName );

        fileDescriptions.append( fileInfo.baseName() );
        directories.append( fileInfo.path() );
    }

    directories.trimMatchingLeft();
    directories.trimLeft( "\\" );

    for ( int i = 0; i < fileNames.count(); i++ )
    {
        if ( !directories[ i ].isEmpty() )
        {
            fileDescriptions[ i ] += '|' + directories[ i ];
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::initializeClusters
(
    void
)
{
    clusters.clear();

    foreach ( QString description1, fileDescriptions )
    {
        QIntMap clusterSize;

        foreach ( QString description2, fileDescriptions )
        {
            int offset = difference( description1, description2 );

            clusterSize[ offset ] += 1;
        }

        clusters.append( clusterSize );
    }
}

/*******************************************************************************
*******************************************************************************/
QIntFloatMap ClassifierImplementation::getVarianceProbablity
(
    void
)
{
    QIntPairList   factors = pairFactor( fileDescriptions.count() );
    QIntList       variance;

    foreach ( QIntPair pair, factors )
    {
        variance.append( pair.first );
        variance.append( pair.second );
    }

    qSort( variance );

    QIntFloatMap result;

    foreach ( int v, variance )
    {
        int     items                = fileDescriptions.count() / v;
        float   varianceProbability  = 0.9f * cosfade( v, 5, 15 ) + 0.1f;
        float   itemCountProbability = 0.9f * cosfade( items, 10, 40 ) + 0.1f;

        result[ v ] = varianceProbability * itemCountProbability;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QIntMap ClassifierImplementation::getClusterSizeCount
(
    void
)
{
    QIntMap result;

    foreach ( QIntMap const & clusterSize, clusters )
    {
        foreach ( int size, clusterSize )
        {
            result[ size ] += 1;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QIntSet ClassifierImplementation::getUnmatchedClusterSize
(
    void
)
{
    QIntSet result;

    foreach ( QIntMap const & clusterSize, clusters )
    {
        if ( ( clusterSize.count( 0 ) != 0 ) && ( clusterSize[ 0 ] > 0 ) )
        {
            result.insert( clusterSize[ 0 ] );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
StemInfoList ClassifierImplementation::getStemClusterInfo
(
    void
)
{
    static int const stemLength[] = { 1, 3, 5, 10 };

    StemInfoList result;

    for ( int j = 0; j < ARRAY_LENGTH( stemLength ); j++ )
    {
        StemInfo        info;
        QStringIntMap   stem;

        foreach ( QString const & description, fileDescriptions )
        {
            stem[ description.left( stemLength[ j ] ) ] += 1;
        }

        info.stemLength = stemLength[ j ];
        info.clusters   = stem.count();

        foreach ( int size, stem )
        {
            info.clusterSize.insert( size );
        }

        result.push_back( info );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::initializeVariance
(
    QIntFloatMap const & varianceProbability
)
{
    variance.clear();

    float gain = 2.0f / accumulateProbability( varianceProbability );

    foreach ( int v, varianceProbability.keys() )
    {
        variance[ v ] = gain * varianceProbability[ v ];
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::addVarianceProbability
(
    int   const variance,
    float const probability
)
{
#ifndef CLASSIFIER_TUNING
    if ( this->variance.count( variance ) != 0 )
#endif /* CLASSIFIER_TUNING */
    {
        this->variance[ variance ] += probability;
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectPopularClusterSizes1
(
    void
)
{
    QIntMap clusterSizeCount;

    foreach ( QIntMap const & clusterSize, clusters )
    {
        foreach ( int size, getAccumulatedClusterSize( clusterSize ) )
        {
            clusterSizeCount[ size ] += 1;
        }
    }

    clusterSizeCount.remove( 1 );
    clusterSizeCount.remove( clusters.count() );

    foreach ( int size, clusterSizeCount.keys() )
    {
        float weight = static_cast< float >( clusterSizeCount[ size ] ) / clusters.count();

        addVarianceProbability( size, weight * weight );
    }
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::getAccumulatedClusterSize
(
    QIntMap const & clusterSize
)
{
    QIntList          result;
    QIntMapIterator   iterator( clusterSize );
    int               accumulated = 0;

    iterator.toBack();

    while ( iterator.hasPrevious() )
    {
        accumulated += iterator.previous().value();

        result.append( accumulated );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectPopularClusterSizes2
(
    QIntMap const & clusterSizeCount
)
{
    QIntMap clusterSize;

    foreach ( int size, clusterSizeCount.keys() )
    {
        if ( size > 1 )
        {
            clusterSize.insertMulti( clusterSizeCount[ size ], size );
        }
    }

    int               index = 0;
    QIntMapIterator   iterator( clusterSize );
    QIntFloatMap      weight;

    iterator.toBack();

    while ( iterator.hasPrevious() )
    {
        iterator.previous();

        weight[ iterator.value() ] = iterator.key() * cosfade( ++index, 3, 7 );
    }

    float gain = qMin( 0.5f * clusterSize.count(), 2.0f ) / accumulateProbability( weight );

    foreach ( int w, weight.keys() )
    {
        addVarianceProbability( w, gain * weight[ w ] );
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectClusterSizeStep
(
    QIntMap const & clusterSizeCount
)
{
    QIntList clusterSize;

    foreach ( int size, clusterSizeCount.keys() )
    {
        clusterSize.push_back( size );
    }

    clusterSize = getRelevantClusterSizes( clusterSize );

    if ( clusterSize.size() > 1 )
    {
        int smallest = clusterSize.takeLast();

        foreach ( int size, clusterSize )
        {
            addVarianceProbability( gcd( size, smallest ), 0.25f );
        }
    }
}

/*******************************************************************************
    Filter-out cluster sizes that differ by 1 from their neighbors
*******************************************************************************/
QIntList ClassifierImplementation::getRelevantClusterSizes
(
    QIntList const & clusterSize
)
{
    QIntList result;

    if ( clusterSize.count() > 1 )
    {
        for ( int i = clusterSize.count() - 1; i > 0; i-- )
        {
            result.append( clusterSize[ i ] );

            if ( ( clusterSize[ i ] - clusterSize[ i - 1 ] ) == 1 )
            {
                break;
            }
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectUniqueItemClusterSize
(
    QIntSet const & clusterSize
)
{
    if ( clusterSize.size() > 0 )
    {
        QIntList values = clusterSize.values();

        qSort( values );

        int size = values.last();

        if ( size > 0 )
        {
            addVarianceProbability( fileDescriptions.count() - size, 0.4f );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectUnmatchedClusterSize
(
    QIntSet const & clusterSize
)
{
    if ( clusterSize.count() > 1 )
    {
        addVarianceProbability( gcd( clusterSize ), 0.5f );
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectSingleItem1
(
    QIntSet const & clusterSize
)
{
    if ( clusterSize.count() == 0 )
    {
        addVarianceProbability( fileDescriptions.count(), 0.75f );
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectItemClusterSize
(
    StemInfoList const & stemClusterInfo
)
{
    QIntFloatMap weight;

    foreach ( StemInfo const & info, stemClusterInfo )
    {
        if ( info.clusters > 1 )
        {
            int variance = gcd( info.clusterSize );

            float   weight1 = 0.7f * ( 1.0f - cosfade( info.clusters, 3, 10 ) ) + 0.3f;
            float   weight2 = 0.5f * ( 1.0f - cosfade( info.clusterSize.size(), 1, 3 ) ) + 0.5f;
            float   weight3;

            if ( variance > 1 )
            {
                weight3 = 0.2f + 0.08f * info.stemLength;
            }
            else
            {
                weight3 = 1.0f / info.stemLength;
            }

            weight[ variance ] += weight1 * weight2 * weight3;
        }
    }

    if ( weight.count() > 0 )
    {
        float gain = ( 0.2f + 0.3f * weight.count() ) / accumulateProbability( weight );

        foreach ( int w, weight.keys() )
        {
            addVarianceProbability( w, gain * weight[ w ] );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::detectSingleItem2
(
    StemInfoList const & stemClusterInfo
)
{
    foreach ( StemInfo const & info, stemClusterInfo )
    {
        if ( info.clusters == 1 )
        {
            int  stemLength  = info.stemLength;
            int  clusterSize = info.clusterSize.values().first();

            addVarianceProbability( clusterSize, 0.005f * stemLength * stemLength + 0.1f );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::applyVarianceProbability
(
    QIntFloatMap const & varianceProbability
)
{
    foreach ( int v, variance.keys() )
    {
        if ( varianceProbability.count( v ) > 0 )
        {
            variance[ v ] *= varianceProbability[ v ];
        }
        else
        {
            variance[ v ] = 0.0f;
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void ClassifierImplementation::validateVariance
(
    void
)
{
    foreach ( int v, variance.keys() )
    {
        if ( variance[ v ] > 0.0f )
        {
            QIntList splitIndices = getSplitIndices( v );

            if ( splitIndices.indexOf( 0 ) != -1 )
            {
                variance[ v ] = 0.0f;
                continue;
            }

            QStringSet names;

            for ( int j = 0; j < fileDescriptions.count(); j++ )
            {
                names.insert( fileDescriptions[ j ].mid( splitIndices[ j ] ) );
            }

            if ( names.count() != v )
            {
                variance[ v ] = 0.0f;
            }
        }
    }
}

/*******************************************************************************
*******************************************************************************/
QIntList ClassifierImplementation::getSplitIndices
(
    int const variance
)
{
    QIntList result;

    foreach ( QIntMap const & clusterSize, clusters )
    {
        QIntMapIterator   iterator( clusterSize );
        int               accumulated = 0;

        iterator.toBack();

        while ( iterator.hasPrevious() )
        {
            iterator.previous();

            accumulated += iterator.value();

            if ( ( accumulated >= variance ) && ( ( accumulated % variance ) == 0 ) )
            {
                result.append( iterator.key() );
                break;
            }
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QStringMap ClassifierImplementation::getItemNames
(
    QStringList const & stems
)
{
    QStringListEx   temp( stems );
    QString         separators( FILE_NAME_SEPARATORS );
    int             offset = temp.findReverseFirstDifference();
    QString         stem   = stems[ 0 ];

    /* Find first separator within identical suffixes */
    while ( ( offset > 0 ) && ( separators.indexOf( stem[ stem.length() - offset ] ) == -1 ) )
    {
        offset--;
    }

    QStringMap result;

    foreach ( QString stem, stems )
    {
        QString   name      = stem.left( stem.length() - offset );
        int       separator = name.indexOf( '|' );

        if ( separator != -1 )
        {
            name = name.left( separator );
        }

        result[ stem ] = name;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QStringMap ClassifierImplementation::getVariantNames
(
    QStringList const & stems
)
{
    QStringListEx names( stems );

    names.trimLeft( FILE_NAME_SEPARATORS );

    QStringIntMap nameCount;

    foreach ( QString const & name, names )
    {
        int separator = name.indexOf( '|' );

        if ( separator != -1 )
        {
            nameCount[ name.left( separator ) ] += 1;
        }
        else
        {
            nameCount[ name ] += 1;
        }
    }

    QStringMap result;

    for ( int i = 0; i < stems.count(); i++ )
    {
        QString   name      = names[ i ];
        int       separator = name.indexOf( '|' );

        if ( separator != -1 )
        {
            name = name.left( separator );

            if ( nameCount[ name ] > 1 )
            {
                name = names[ i ].mid( separator + 1 ) + '\\' + name;
            }
        }

        result[ stems[ i ] ] = name;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
float ClassifierImplementation::accumulateProbability
(
    QIntFloatMap const & probability
)
{
    float result = 0.0f;

    foreach ( float p, probability )
    {
        result += p;
    }

    return result;
}

/******************************************************************************/
