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
