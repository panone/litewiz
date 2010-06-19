<?php

include_once( 'utility.php' );

/*******************************************************************************
*******************************************************************************/
class Classifier
{
    private $fileName;
    private $codecCount;
    private $itemName;
    private $codecName;

    /***************************************************************************
    ***************************************************************************/
    public function __construct()
    {
        $this->Initialize();
    }

    /***************************************************************************
    ***************************************************************************/
    private function Initialize()
    {
        $this->fileName   = array();
        $this->codecCount = array();
        $this->itemName   = array();
        $this->codecName  = array();
    }

    /***************************************************************************
    ***************************************************************************/
    public function Classify( $fileName )
    {
        $this->Initialize();

        foreach ( $fileName as $fn )
        {
            $this->fileName[ $fn ] = new FileNameMatch( $fn, $fileName );
        }

        $clusterSizeCount = $this->GetClusterSizeCount();

        $this->DetectClusterSizeStep( array_keys( $clusterSizeCount ) );

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
                @$result[ $size ] += $count;
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

    /***************************************************************************
    ***************************************************************************/
    private function DetectClusterSizeStep( $clusterSize )
    {
        $clusterSize = $this->GetRelevantClusterSizes( $clusterSize );
        $count       = count( $clusterSize );

        if ( $count > 1 )
        {
            $smallest = array_pop( $clusterSize );

            foreach ( $clusterSize as $size )
            {
                @$this->codecCount[ gcd( $size, $smallest ) ] += 0.2;
            }
        }

        print_r( $this->codecCount );
    }

    /***************************************************************************
        Filter-out cluster sizes that differ by 1 from their neighbours
    ***************************************************************************/
    private function GetRelevantClusterSizes( $clusterSize )
    {
        $result = array();
        $count  = count( $clusterSize );

        if ( $count > 1 )
        {
            for ( $i = $count - 1; $i > 0; $i-- )
            {
                $result[] = $clusterSize[ $i ];

                if ( ( $clusterSize[ $i ] - $clusterSize[ $i - 1 ] ) == 1 )
                {
                    break;
                }
            }
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

            @$result[ $size ] += 1;
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
