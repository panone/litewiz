<?php

include_once( 'utility.php' );

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

        $clusterSizeCount = $this->GetClusterSizeCount();

        return array( $this->itemName, $this->codecName );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetClusterSizeCount()
    {
        $result = array();

        foreach ( $this->fileName as $fn )
        {
            foreach ( $fn->GetClusterSizeCount() as $size => $count )
            {
                $result[ $size ] = isset( $result[ $size ] ) ? $result[ $size ] + $count : $count;
            }
        }

        ksort( $result );

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
    private $cluster;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $fileName, $list )
    {
        $this->fileName = $fileName;
        $this->cluster  = array();

        foreach ( $list as $fn )
        {
            $offset = strdiff( $fileName, $fn );

            $this->cluster[ $offset ][] = $fn;
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function GetClusterSizeCount()
    {
        $result = array();

        foreach( $this->cluster as $cluster )
        {
            $size = count( $cluster );

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
        $length = array_keys( $this->cluster );

        if ( $order < count( $length ) )
        {
            rsort( $length );

            $result = count( $this->cluster[ $length[ $order ] ] );
        }

        return $result;
    }
}
