/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QMap>
#include <QPair>
#include <QString>
#include <algorithm>
#include "utility.h"

using namespace std;

/*******************************************************************************
    Returns character offset of the first mismatch between two strings
*******************************************************************************/
int difference
(
    QString const & string1,
    QString const & string2
)
{
    int           result = 0;
    QChar const * data1  = string1.constData();
    QChar const * data2  = string2.constData();
    int           length = min( string1.length(), string2.length() );

    while ( ( result < length ) && ( *data1++ == *data2++ ) )
    {
        ++result;
    }

    return result;
}

/*******************************************************************************
    Returns array of prime factors of an integer
*******************************************************************************/
QIntList primeFactor
(
    int const number
)
{
    QIntList   result;
    int        factor   = 2;
    int        dividend = number;

    while ( ( factor * factor ) <= dividend )
    {
        if ( ( dividend % factor ) == 0 )
        {
            result.append( factor );

            dividend /= factor;
        }
        else
        {
            ++factor;
        }
    }

    result.append( dividend );

    return result;
}

/*******************************************************************************
    Returns array of all possible factor pairs of an integer
*******************************************************************************/
QIntPairList pairFactor
(
    int const number
)
{
    QMap< int, int >   factors;
    QIntList           primes   = primeFactor( number );
    int                setSize1 = 1;
    int                setSize2 = primes.count() - setSize1;

    factors[ 1 ] = number;

    if ( primes.count() == 2 )
    {
        factors[ primes[ 0 ] ] = primes[ 1 ];
    }

    while ( setSize1 <= setSize2 )
    {
        for ( int i = 0; i < ( primes.count() - ( setSize1 - 1 ) ); i++ )
        {
            int   factor1 = 1;
            int   factor2 = 1;

            for ( int j = 0; j < setSize1; j++ )
            {
                factor1 *= primes[ i + j ];
            }

            for ( int k = 0; k < i; k++ )
            {
                factor2 *= primes[ k ];
            }

            for ( int k = i + setSize1; k < primes.count(); k++ )
            {
                factor2 *= primes[ k ];
            }

            factors[ min( factor1, factor2 ) ] = max( factor1, factor2 );
        }

        setSize2 = primes.count() - ++setSize1;
    }

    QIntPairList result;

    foreach ( int factor, factors.keys() )
    {
        result.append( QIntPair( factor, factors[ factor ] ) );
    }

    return result;
}

/******************************************************************************/
