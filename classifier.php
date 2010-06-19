<?php

/*******************************************************************************
*******************************************************************************/
class Classifier
{
    private $fileName;
    private $itemName;
    private $codecName;

    /***************************************************************************
    ***************************************************************************/
    public function __construct()
    {
        $this->fileName  = array();
        $this->itemName  = array();
        $this->codecName = array();
    }

    /***************************************************************************
    ***************************************************************************/
    public function Classify( $fileName )
    {
        $this->fileName  = $fileName;
        $this->itemName  = array();
        $this->codecName = array();

        $match = array();

        foreach ( $fileName as $fn )
        {
            $match[ $fn ] = new FileNameMatch( $fn, $fileName );

            print( str_pad( $fn, 50 ) . " : " );
            print( "0 -> " . $match[ $fn ]->GetMatchesCount( 0 ) . ", " );
            print( "1 -> " . $match[ $fn ]->GetMatchesCount( 1 ) . ", " );
            print( "2 -> " . $match[ $fn ]->GetMatchesCount( 2 ) . "\n" );
        }

        print_r( $match[ $fileName[ 0 ] ]->GetGroupSizeCount() );
        print_r( $match[ $fileName[ 69 ] ]->GetGroupSizeCount() );

        $groupSizeCount = array();

        foreach ( $match as $m )
        {
            foreach ( $m->GetGroupSizeCount() as $size => $count )
            {
                $groupSizeCount[ $size ] = isset( $groupSizeCount[ $size ] ) ? $groupSizeCount[ $size ] + $count : $count;
            }
        }

        print_r( $groupSizeCount );

        foreach ( $groupSizeCount as $size => $count )
        {
            print( $size . "\t" . $count . "\n" );
        }

        return array( $this->itemName, $this->codecName );
    }
}

/*******************************************************************************
*******************************************************************************/
class FileNameMatch
{
    private $fileName;
    private $matchLength;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $fileName, $list )
    {
        $this->fileName    = $fileName;
        $this->matchLength = array();

        foreach ( $list as $fn )
        {
            $offset = $this->FindFirstDifference( $fileName, $fn );

            $this->matchLength[ $offset ][] = $fn;
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function FindFirstDifference( $string1, $string2 )
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
    ***************************************************************************/
    public function GetGroupSizeCount()
    {
        $result = array();

        foreach( $this->matchLength as $ml )
        {
            $size = count( $ml );

            $result[ $size ] = isset( $result[ $size ] ) ? $result[ $size ] + 1 : 1;
        }

        return $result;
    }

    /***************************************************************************
        Returns number of matches in the order from the longest match to the
        shortest one.
        Parameters:
            $order: 0 - the longest match, 1 - shorter one, and so on.
    ***************************************************************************/
    public function GetMatchesCount( $order )
    {
        $result = 0;
        $length = array_keys( $this->matchLength );

        if ( $order < count( $length ) )
        {
            rsort( $length );

            $result = count( $this->matchLength[ $length[ $order ] ] );
        }

        return $result;
    }
}
