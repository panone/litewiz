<?php

/***************************************************************************
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
