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
    public function Classify( $fileName )
    {
        $this->Initialize();

        $this->log = new ClassifierLog();

        foreach ( $fileName as $fn )
        {
            $this->fileName[ $fn ] = new FileNameMatch( $fn, $fileName );
        }

        $possibleCodecCount    = $this->GetPossibleCodecCounts();
        $codecCountProbability = $this->GetCodecCountProbability( $possibleCodecCount );
        $clusterSizeCount      = $this->GetClusterSizeCount();
        $unmatchedClusterSize  = $this->GetUnmatchedClusterSize();

        $this->SetCodecCountProbability( $codecCountProbability );
        $this->SelectPopularClusterSizes( $clusterSizeCount );
        $this->DetectClusterSizeStep( array_keys( $clusterSizeCount ) );
        $this->DetectUniqueItemClusterSize( $unmatchedClusterSize );
        $this->DetectUnmatchedClusterSize( $unmatchedClusterSize );
        $this->DetectSingleItem( $unmatchedClusterSize );

        $this->ApplyCodecCountProbability( $codecCountProbability );

        return array( $this->itemName, $this->codecName );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetPossibleCodecCounts()
    {
        $files  = count( $this->fileName );
        $factor = pairfact( $files );

        foreach ( $factor as $pair )
        {
            $result[] = $pair[ 0 ];
            $result[] = $pair[ 1 ];
        }

        asort( $result );

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetCodecCountProbability( $codecCount )
    {
        $files = count( $this->fileName );

        foreach ( $codecCount as $codecs )
        {
            $items = $files / $codecs;

            $codecsProbability = 0.9 * cosfade( $codecs, 5, 15 ) + 0.1;
            $itemsProbability  = 0.9 * cosfade( $items, 10, 40 ) + 0.1;

            $result[ $codecs ] = $codecsProbability * $itemsProbability;
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function SetCodecCountProbability( $probability )
    {
        $gain = 2.0 / array_sum( $probability );

        foreach ( $probability as $codecs => $p )
        {
            @$this->codecCount[ $codecs ] += $gain * $p;
        }

        $this->log->LogCodecCount( 'SetCodecCountProbability', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function ApplyCodecCountProbability( $probability )
    {
        foreach ( array_keys( $this->codecCount ) as $codecs )
        {
            $p = @floatval( $probability[ $codecs ] );

            $this->codecCount[ $codecs ] *= $p;
        }

        $this->log->LogCodecCount( 'ApplyCodecCountProbability', $this->codecCount );
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

        $count            = count( $clusterSizeCount );
        $gain             = min( 0.125 * $count, 1 );
        $clusterSizeCount = array_slice( $clusterSizeCount, 0, min( $count, 4 ), TRUE );
        $maxCount         = max( $clusterSizeCount );

        foreach ( $clusterSizeCount as $size => $count )
        {
            $weight[ $size ] = $count / $maxCount;
        }

        $gain *= 2.0 / array_sum( $weight );

        foreach ( $clusterSizeCount as $size => $count )
        {
            @$this->codecCount[ $size ] += $gain * $weight[ $size ];
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
    private function GetUnmatchedClusterSize()
    {
        foreach ( $this->fileName as $fn )
        {
            $result[] = $fn->GetUnmatchedClusterSize();
        }

        return array_values( array_unique( $result ) );
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectUniqueItemClusterSize( $clusterSize )
    {
        $size = max( $clusterSize );

        if ( $size > 0 )
        {
            @$this->codecCount[ count( $this->fileName ) - $size ] += 0.4;
        }

        $this->log->LogCodecCount( 'DetectUniqueItemClusterSize', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectUnmatchedClusterSize( $clusterSize )
    {
        $sizes = count( $clusterSize );

        if ( $sizes > 1 )
        {
            $size = $clusterSize[ 0 ];

            for ( $i = 1; ( $size > 1 ) && ( $i < $sizes ); $i++ )
            {
                $size = gcd( $size, $clusterSize[ $i ] );
            }

            @$this->codecCount[ $size ] += 0.5;
        }

        $this->log->LogCodecCount( 'DetectUnmatchedClusterSize', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectSingleItem( $clusterSize )
    {
        if ( ( count( $clusterSize ) == 1 ) && ( $clusterSize[ 0 ] == 0 ) )
        {
            @$this->codecCount[ count( $this->fileName ) ] += 0.75;
        }

        $this->log->LogCodecCount( 'DetectSingleItem', $this->codecCount );
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
    private $text;

    /***************************************************************************
    ***************************************************************************/
    public function __construct()
    {
        $this->label       = array();
        $this->clusterSize = array();
        $this->codecCount  = array();
        $this->text        = '';
    }

    /***************************************************************************
    ***************************************************************************/
    public function Log( $line )
    {
        $this->text .= $line . "\n";
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
        $this->RenderCodecCount( $sink );

        $sink->Write( '<div class="clearer"></div>' );

        if ( $this->text != '' )
        {
            $this->RenderTextLog( $sink );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderClusterSize( $sink )
    {
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

        $sink->OpenReportBlock( 'Cluster size distribution', 'cluster-size' );
        $sink->Write( $image );
        $sink->CloseReportBlock();
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderCodecCount( $sink )
    {
        static $color = array( '4D89F9', 'FFCEB4', 'BEF3A9', '96DEE4', 'DEB3FF', 'FF94C1', 'DDDB4A', '22C778', 'A6C7E3' );

        ksort( $this->codecCount );

        $snapshots = count( $this->label );
        $max       = ceil( $this->GetMaxCodecCountWight() + 0.5 );

        for ( $i = 0; $i < $snapshots; $i++ )
        {
            $series = array();

            foreach ( $this->codecCount as $weight )
            {
                $series[] = $weight[ $i ];
            }

            $data[] = implode( ',', $series );
        }

        $chart[] = 'chs=400x200';
        $chart[] = 'cht=lc';
        $chart[] = 'chd=t:' . implode( '|', $data );
        $chart[] = "chds=0,$max";
        $chart[] = 'chco=' . implode( ',', array_slice( $color, 0, $snapshots ) );
        $chart[] = 'chxt=x,y';
        $chart[] = "chxr=1,0,$max";
        $chart[] = 'chxl=0:|' . implode( '|', array_keys( $this->codecCount ) );

        $image = '<img src="http://chart.apis.google.com/chart?' . implode( '&amp;', $chart ) . '" />';

        $sink->OpenReportBlock( 'Codecs number probability distribution', 'codec-count' );
        $sink->Write( $image );
        $sink->CloseReportBlock();
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetMaxCodecCountWight()
    {
        foreach ( $this->codecCount as $weight )
        {
            $max[] = max( $weight );
        }

        return max( $max );
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderTextLog( $sink )
    {
        $sink->OpenReportBlock( 'Log', 'log' );
        $sink->Write( "<pre>$this->text</pre>" );
        $sink->CloseReportBlock();
    }
}
