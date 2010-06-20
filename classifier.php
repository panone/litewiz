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
    private $log;

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
        $this->log        = NULL;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Classify( $fileName )
    {
        $this->Initialize();

        $this->log = new ClassifierLog();

        foreach ( $fileName as $fn )
        {
            $this->fileName[ $fn ] = new FileNameMatch( $fn, $fileName );
        }

        $clusterSizeCount = $this->GetClusterSizeCount();

        $this->SelectPopularClusterSizes( $clusterSizeCount );
        $this->DetectClusterSizeStep( array_keys( $clusterSizeCount ) );
        $this->DetectUniqueItemClusterSize();

        return array( $this->itemName, $this->codecName );
    }

    /***************************************************************************
    ***************************************************************************/
    public function Dump()
    {
        if ( $this->log != NULL )
        {
            $this->log->Dump();
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function RenderReport( $sink )
    {
        if ( $this->log != NULL )
        {
            $this->log->RenderReport( $sink );
        }
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

        $this->log->LogClusterSize( $result );

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function SelectPopularClusterSizes( $clusterSizeCount )
    {
        if ( isset( $clusterSizeCount[ 1 ] ) )
        {
            unset( $clusterSizeCount[ 1 ] );
        }

        arsort( $clusterSizeCount );

        $clusterSize = array_keys( $clusterSizeCount );
        $count       = min( count( $clusterSize ), 4 );

        for ( $i = 0; $i < $count; $i++ )
        {
            @$this->codecCount[ $clusterSize[ $i ] ] += 1 / pow( 2, $i );
        }

        $this->log->LogCodecCount( 'SelectPopularClusterSizes', $this->codecCount );
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
                @$this->codecCount[ gcd( $size, $smallest ) ] += 0.25;
            }
        }

        $this->log->LogCodecCount( 'DetectClusterSizeStep', $this->codecCount );
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

    /***************************************************************************
    ***************************************************************************/
    private function DetectUniqueItemClusterSize()
    {
        $size = $this->GetMaxUnmatchedClusterSize();

        if ( $size > 0 )
        {
            @$this->codecCount[ count( $this->fileName ) - $size ] += 0.5;
        }

        $this->log->LogCodecCount( 'DetectUniqueItemClusterSize', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetMaxUnmatchedClusterSize()
    {
        $result = 0;

        foreach ( $this->fileName as $fn )
        {
            $result = max( $result, $fn->GetUnmatchedClusterSize() );
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
    ***************************************************************************/
    public function GetUnmatchedClusterSize()
    {
        $result = 0;

        if ( isset( $this->cluster[ 0 ] ) )
        {
            $result = count( $this->cluster[ 0 ] );
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

/*******************************************************************************
*******************************************************************************/
class ClassifierLog
{
    private $label;
    private $clusterSize;
    private $codecCount;

    /***************************************************************************
    ***************************************************************************/
    public function __construct()
    {
        $this->label       = array();
        $this->clusterSize = array();
        $this->codecCount  = array();
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogClusterSize( $clusterSize )
    {
        $this->clusterSize = $clusterSize;
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogCodecCount( $label, $codecCount )
    {
        $snapshots = count( $this->label );

        foreach ( $codecCount as $count => $weight )
        {
            if ( !isset( $this->codecCount[ $count ] ) )
            {
                for ( $i = 0; $i < $snapshots; $i++ )
                {
                    $this->codecCount[ $count ][ $i ] = 0;
                }
            }

            $this->codecCount[ $count ][] = $weight;
        }

        $this->label[] = $label;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Dump()
    {
        $this->DumpClusterSize();
        $this->DumpCodecCount();
    }

    /***************************************************************************
    ***************************************************************************/
    private function DumpClusterSize()
    {
        print( "GetClusterSizeCount\n" );

        foreach ( $this->clusterSize as $size => $count )
        {
            print( $size . "\t" . $count . "\n" );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function DumpCodecCount()
    {
        ksort( $this->codecCount );

        $snapshots = count( $this->label );

        for ( $i = 0; $i < $snapshots; $i++ )
        {
            print( '   ' . str_pad( '', $i * 8 ) . $this->label[ $i ] . "\n" );
        }

        foreach ( $this->codecCount as $count => $weight )
        {
            print( str_pad( $count, 3 ) );

            for ( $i = 0; $i < $snapshots; $i++ )
            {
                print( sprintf( '%-8.3f', $weight[ $i ] ) );
            }

            print( "\n" );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function RenderReport( $sink )
    {
        $this->RenderClusterSize( $sink );
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderClusterSize( $sink )
    {
        $sink->Write( '<div class="cluster-size">' );
        $sink->Write( '<h3>Cluster size distribution <span class="expand">&laquo;</span></h3>' );

        $max = ceil( max( $this->clusterSize ) / 10 ) * 10;
        $chart[] = 'chs=400x200';
        $chart[] = 'cht=bvs';
        $chart[] = 'chd=t:' . implode( ',', $this->clusterSize );
        $chart[] = "chds=0,$max";
        $chart[] = 'chco=4D89F9';
        $chart[] = 'chxt=x,y';
        $chart[] = "chxr=1,0,$max";
        $chart[] = 'chxl=0:|' . implode( '|', array_keys( $this->clusterSize ) );
        $chart[] = 'chm=N,FFFFFF,0,,9,,c';

        $image = '<img src="http://chart.apis.google.com/chart?' . implode( '&amp;', $chart ) . '" />';

        $sink->Write( $image );
        $sink->Write( '</div>' );
    }
}
