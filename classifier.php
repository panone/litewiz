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
        $this->fileName  = array();
        $this->itemName  = array();
        $this->codecName = array();

        foreach ( $fileName as $fn )
        {
            $this->fileName[ $fn ] = new FileNameMatch( $fn, $fileName );
        }

        $groupSizeCount = $this->GetGroupSizeCount();

        return array( $this->itemName, $this->codecName );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetGroupSizeCount()
    {
        $result = array();

        foreach ( $this->fileName as $fn )
        {
            foreach ( $fn->GetGroupSizeCount() as $size => $count )
            {
                $result[ $size ] = isset( $result[ $size ] ) ? $result[ $size ] + $count : $count;
            }
        }

        print_r( $result );

        foreach ( $result as $size => $count )
        {
            print( $size . "\t" . $count . "\n" );
        }

        return $result;
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
