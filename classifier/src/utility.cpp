/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QString>
#include <QStringList>
#include <math.h>
#include "utility.h"

/*******************************************************************************
*******************************************************************************/
QStringListEx::QStringListEx
(
    void
) :
    QStringList()
{
}

/*******************************************************************************
*******************************************************************************/
QStringListEx::QStringListEx
(
    QStringList const & other
) :
    QStringList( other )
{
}

/*******************************************************************************
*******************************************************************************/
void QStringListEx::trimLeft
(
    QString const & target
)
{
    QMutableListIterator< QString > iterator( *this );

    while ( iterator.hasNext() )
    {
        QString & string = iterator.next();
        int       index  = 0;

        while ( target.indexOf( string[ index ] ) != -1 )
        {
            index++;
        }

        if ( index > 0 )
        {
            string = string.mid( index );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
void QStringListEx::trimRight
(
    int const count
)
{
    QMutableListIterator< QString > iterator( *this );

    while ( iterator.hasNext() )
    {
        QString & string = iterator.next();

        string = string.left( string.length() - count );
    }
}

/*******************************************************************************
*******************************************************************************/
void QStringListEx::trimMatchingLeft
(
    void
)
{
    int left = findFirstDifference();

    if ( left > 0 )
    {
        QMutableListIterator< QString > iterator( *this );

        while ( iterator.hasNext() )
        {
            QString & string = iterator.next();

            string = string.mid( left );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
int QStringListEx::findFirstDifference
(
    void
)
    const
{
    int    length     = getMinLength();
    bool   difference = false;
    int    offset;

    for ( offset = 0; offset < length; offset++ )
    {
        QChar reference = at( 0 )[ offset ];

        foreach ( QString const & string, *this )
        {
            if ( string[ offset ] != reference )
            {
                difference = true;
                break;
            }
        }

        if ( difference )
        {
            break;
        }
    }

    return offset;
}

/*******************************************************************************
*******************************************************************************/
int QStringListEx::findReverseFirstDifference
(
    void
)
    const
{
    int   length = getMinLength();
    int   offset = 0;

    if ( length > 0 )
    {
        bool difference = false;

        for ( offset = 1; offset <= length; offset++ )
        {
            QChar reference = at( 0 )[ at( 0 ).length() - offset ];

            foreach ( QString const & string, *this )
            {
                if ( string[ string.length() - offset ] != reference )
                {
                    difference = true;
                    break;
                }
            }

            if ( difference )
            {
                break;
            }
        }
    }

    return offset - 1;
}

/*******************************************************************************
*******************************************************************************/
int QStringListEx::getMinLength
(
    void
)
    const
{
    int result = 0;

    if ( count() > 0 )
    {
        QListIterator< QString > iterator( *this );

        result = iterator.next().length();

        while ( iterator.hasNext() )
        {
            result = qMin( result, iterator.next().length() );
        }
    }

    return result;
}

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
