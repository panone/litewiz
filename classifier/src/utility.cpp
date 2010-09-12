/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QString>
#include <math.h>
#include "utility.h"

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
    int           length = qMin( string1.length(), string2.length() );

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

            factors[ qMin( factor1, factor2 ) ] = qMax( factor1, factor2 );
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

/*******************************************************************************
    Returns a cosine fade-out gain
*******************************************************************************/
float cosfade
(
    int const value,
    int const fadeStart,
    int const fadeEnd
)
{
    static float const pi = 3.14159265358f;

    float result;

    if ( value <= fadeStart )
    {
        result = 1.0f;
    }
    else
    {
        if ( value >= fadeEnd )
        {
            result = 0.0f;
        }
        else
        {
            result = 0.5f * ( cos( pi * ( value - fadeStart ) / ( fadeEnd - fadeStart ) ) + 1.0f );
        }
    }

    return result;
}

/*******************************************************************************
    Returns gretest common divider of two positive integers
*******************************************************************************/
int gcd
(
    int const number1,
    int const number2
)
{
    int   result   = qMin( number1, number2 );
    int   dividend = qMax( number1, number2 );
    int   reminder = dividend % result;

    while ( reminder != 0 )
    {
        dividend = result;
        result   = reminder;
        reminder = dividend % result;
    }

    return result;
}

/*******************************************************************************
    Returns gretest common divider of list of positive integers
*******************************************************************************/
int gcd
(
    QIntList const & numbers
)
{
    int result = 0;

    if ( numbers.count() > 0 )
    {
        QIntListIterator iterator( numbers );

        result = iterator.next();

        while ( ( result > 1 ) && iterator.hasNext() )
        {
            result = gcd( result, iterator.next() );
        }
    }

    return result;
}

/*******************************************************************************
    Returns gretest common divider of set of positive integers
*******************************************************************************/
int gcd
(
    QIntSet const & numbers
)
{
    int result = 0;

    if ( numbers.count() > 0 )
    {
        QIntSetIterator iterator( numbers );

        result = iterator.next();

        while ( ( result > 1 ) && iterator.hasNext() )
        {
            result = gcd( result, iterator.next() );
        }
    }

    return result;
}

/******************************************************************************/
