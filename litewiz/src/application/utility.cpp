/*******************************************************************************
*******************************************************************************/

#include <QString>

/*******************************************************************************
*******************************************************************************/
bool naturalCompare
(
    QString const & string1,
    QString const & string2
)
{
    int       length = qMin( string1.length(), string2.length() );
    int       index  = 0;
    QString   number;

    while ( ( index < length ) && ( string1[ index ] == string2[ index ] ) )
    {
        if ( string1[ index ].isNumber() )
        {
            number.append( string1[ index ] );
        }
        else
        {
            number.clear();
        }

        index++;
    }

    bool result;

    if ( !number.isEmpty() || ( ( index < length ) && string1[ index ].isNumber() && string2[ index ].isNumber() ) )
    {
        QString   number1 = number;
        QString   number2 = number;
        int       index1  = index;
        int       index2  = index;

        while ( ( index1 < string1.length() ) && string1[ index1 ].isNumber() )
        {
            number1.append( string1[ index1++ ] );
        }

        while ( ( index2 < string2.length() ) && string2[ index2 ].isNumber() )
        {
            number2.append( string2[ index2++ ] );
        }

        index1 = 0;
        index2 = 0;

        while ( ( index1 < number1.length() ) && ( number1[ index1 ] == QChar( '0' ) ) )
        {
            index1++;
        }

        while ( ( index2 < number2.length() ) && ( number2[ index2 ] == QChar( '0' ) ) )
        {
            index2++;
        }

        if ( index1 == index2 )
        {
            if ( index1 == number1.length() )
            {
                return false;
            }
            else
            {
                if ( index2 == number2.length() )
                {
                    return true;
                }
                else
                {
                    result = number1.toInt() < number2.toInt();
                }
            }
        }
        else
        {
            result = index1 > index2;
        }
    }
    else
    {
        if ( index < length )
        {
            result = string1[ index ] < string2[ index ];
        }
        else
        {
            result = string1.length() < string2.length();
        }
    }

    return result;
}

/******************************************************************************/
