<?php

/***************************************************************************
    Returns character offset of the first mismatch between two strings
***************************************************************************/
function strdiff( $string1, $string2 )
{
    $length = min( strlen( $string1 ), strlen( $string2 ) );

    for ( $i = 0; $i < $length; $i++ )
    {
        if ( $string1{ $i } != $string2{ $i } )
        {
            break;
        }
    }

    return $i;
}

/***************************************************************************
    Returns gretest common divider of two positive integers
***************************************************************************/
function gcd( $number1, $number2 )
{
    $number1 = intval( $number1 );
    $number2 = intval( $number2 );

    if ( ( $number1 > 0 ) && ( $number2 > 0 ) )
    {
        $reminder = $number1 % $number2;

        while ( $reminder != 0 )
        {
            $number1  = $number2;
            $number2  = $reminder;
            $reminder = $number1 % $number2;
        }
    }
    else
    {
        $number2 = 0;
    }

    return $number2;
}

/***************************************************************************
    Returns array of prime factors of an integer
***************************************************************************/
function primefact( $number )
{
    $result = array();
    $factor = 2;

    while ( ( $factor * $factor ) <= $number )
    {
        if ( ( $number % $factor ) == 0 )
        {
            $result[] = $factor;
            $number  /= $factor;
        }
        else
        {
            $factor++;
        }
    }

    $result[] = $number;

    return $result;
}

/***************************************************************************
    Returns array of all possible factor pairs of an integer
***************************************************************************/
function pairfact( $number )
{
    $prime  = primefact( $number );
    $primes = count( $prime );
    $setSize1 = 1;
    $setSize2 = $primes - $setSize1;
    $factor   = array( 1 => $number );

    if ( $primes == 2 )
    {
        $factor[ $prime[ 0 ] ] = $prime[ 1 ];
    }

    while ( $setSize1 <= $setSize2 )
    {
        for ( $i = 0; $i < ( $primes - ( $setSize1 - 1 ) ); $i++ )
        {
            $factor1 = 1;
            $factor2 = 1;

            for ( $j = 0; $j < $setSize1; $j++ )
            {
                $factor1 *= $prime[ $i + $j ];
            }

            for ( $k = 0; $k < $i; $k++ )
            {
                $factor2 *= $prime[ $k ];
            }

            for ( $k = $i + $setSize1; $k < $primes; $k++ )
            {
                $factor2 *= $prime[ $k ];
            }

            $factor[ min( $factor1, $factor2 ) ] = max( $factor1, $factor2 );
        }

        $setSize1++;
        $setSize2 = $primes - $setSize1;
    }

    foreach ( $factor as $factor1 => $factor2 )
    {
        $result[] = array( $factor1, $factor2 );
    }

    return $result;
}
