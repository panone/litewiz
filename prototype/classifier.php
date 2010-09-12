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

        $codecCountProbability = $this->GetCodecCountProbability();
        $clusterSizeCount      = $this->GetClusterSizeCount();
        $unmatchedClusterSize  = $this->GetUnmatchedClusterSize();
        $stemClusterCount      = $this->GetStemClusterCount();

        $this->SetCodecCountProbability( $codecCountProbability );
        $this->SelectPopularClusterSizes1( $clusterSizeCount );
        $this->SelectPopularClusterSizes2();
        $this->DetectClusterSizeStep( array_keys( $clusterSizeCount ) );
        $this->DetectUniqueItemClusterSize( $unmatchedClusterSize );
        $this->DetectUnmatchedClusterSize( $unmatchedClusterSize );
        $this->DetectSingleItem1( $unmatchedClusterSize );
        $this->DetectItemClusterSize( $stemClusterCount );
        $this->DetectSingleItem2( $stemClusterCount );

        $this->ApplyCodecCountProbability( $codecCountProbability );

        $this->SplitFileNames( $this->GetCodecsCount() );

        $this->log->Log( "\nitems:" ); foreach ( $this->itemName as $i ) $this->log->Log( $i );
        $this->log->Log( "\ncodecs:" ); foreach ( $this->codecName as $c ) $this->log->Log( $c );

        return array( $this->itemName, $this->codecName );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetCodecCountProbability()
    {
        $files  = count( $this->fileName );
        $factor = pairfact( $files );

        foreach ( $factor as $pair )
        {
            $codecCount[] = $pair[ 0 ];
            $codecCount[] = $pair[ 1 ];
        }

        asort( $codecCount );

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
    private function SelectPopularClusterSizes1( $clusterSizeCount )
    {
        if ( isset( $clusterSizeCount[ 1 ] ) )
        {
            unset( $clusterSizeCount[ 1 ] );
        }

        arsort( $clusterSizeCount );

        $i = 0;

        foreach ( $clusterSizeCount as $size => $count )
        {
            $weight[ $size ] = $count * cosfade( ++$i, 3, 7 );
        }

        $gain = min( 0.5 * count( $clusterSizeCount ), 2.0 ) / array_sum( $weight );

        foreach ( $weight as $size => $w )
        {
            @$this->codecCount[ $size ] += $gain * $w;
        }

        $this->log->LogCodecCount( 'SelectPopularClusterSizes1', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function SelectPopularClusterSizes2()
    {
        foreach ( $this->fileName as $fn )
        {
            foreach ( $fn->GetAccumulatedClusterSize() as $size )
            {
                @$clusterSizeCount[ $size ] += 1;
            }
        }

        ksort( $clusterSizeCount );

        $this->log->LogClusterSize( $clusterSizeCount );

        $files = count( $this->fileName );

        unset( $clusterSizeCount[ 1 ] );
        unset( $clusterSizeCount[ $files ] );

        foreach ( $clusterSizeCount as $size => $count )
        {
            $weight = $count / $files;

            @$this->codecCount[ $size ] += $weight * $weight;
        }

        $this->log->LogCodecCount( 'SelectPopularClusterSizes2', $this->codecCount );
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
            @$this->codecCount[ gcd( $clusterSize ) ] += 0.5;
        }

        $this->log->LogCodecCount( 'DetectUnmatchedClusterSize', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectSingleItem1( $clusterSize )
    {
        if ( ( count( $clusterSize ) == 1 ) && ( $clusterSize[ 0 ] == 0 ) )
        {
            @$this->codecCount[ count( $this->fileName ) ] += 0.75;
        }

        $this->log->LogCodecCount( 'DetectSingleItem1', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetStemClusterCount()
    {
        static $stemLength = array( 1, 3, 5, 10 );

        $fileName = array_keys( $this->fileName );

        foreach ( $stemLength as $length )
        {
            $stem = array();

            foreach ( $fileName as $fn )
            {
                @$stem[ substr( $fn, 0, $length ) ] += 1;
            }

            $count   = count( $stem );
            $cluster = array_values( array_unique( $stem ) );

            $result[] = array( 'length' => $length, 'clusters' => $count, 'cluster' => $cluster );
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectItemClusterSize( $stemClusterCount )
    {
        $weight = array();

        foreach ( $stemClusterCount as $stem )
        {
            $stemLength  = $stem[ 'length' ];
            $clusters    = $stem[ 'clusters' ];
            $clusterSize = $stem[ 'cluster' ];

            if ( $clusters > 1 )
            {
                $codecs = gcd( $clusterSize );

                $weight1 = 0.7 * ( 1.0 - cosfade( $clusters, 3, 10 ) ) + 0.3;
                $weight2 = 0.5 * ( 1.0 - cosfade( count( $clusterSize ), 1, 3 ) ) + 0.5;

                if ( $codecs > 1 )
                {
                    $weight3 = 0.2 + 0.08 * $stemLength;
                }
                else
                {
                    $weight3 = 1.0 / $stemLength;
                }

                @$weight[ $codecs ] += $weight1 * $weight2 * $weight3;
            }
        }

        if ( !empty( $weight ) )
        {
            $gain = ( 0.2 + 0.3 * count( $weight ) ) / array_sum( $weight );

            foreach ( $weight as $codecs => $w )
            {
                @$this->codecCount[ $codecs ] += $gain * $w;
            }
        }

        $this->log->LogCodecCount( 'DetectItemClusterSize', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function DetectSingleItem2( $stemClusterCount )
    {
        foreach ( $stemClusterCount as $stem )
        {
            $stemLength = $stem[ 'length' ];
            $clusters   = $stem[ 'clusters' ];

            if ( $clusters == 1 )
            {
                $codecs = $stem[ 'cluster' ][ 0 ];

                @$this->codecCount[ $codecs ] += 0.005 * $stemLength * $stemLength + 0.1;
            }
        }

        $this->log->LogCodecCount( 'DetectSingleItem2', $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetCodecsCount()
    {
        arsort( $this->codecCount );
        reset( $this->codecCount );

        return key( $this->codecCount );
    }

    /***************************************************************************
    ***************************************************************************/
    private function SplitFileNames( $codecs )
    {
        foreach ( $this->fileName as $fn )
        {
            list( $i, $c ) = $fn->Split( $codecs );

            $itemName[ $i ]  = TRUE;
            $codecName[ $c ] = TRUE;
        }

        $this->itemName = array_keys( $itemName );

        if ( count( $codecName ) > 1 )
        {
            $this->codecName = array_keys( $codecName );
        }
        else
        {
            $this->codecName[ 0 ] = 'ref';
        }
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

        krsort( $this->cluster );
    }

    /***************************************************************************
    ***************************************************************************/
    public function GetClusterSizeCount()
    {
        $result = array();

        foreach ( $this->cluster as $cluster )
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
    ***************************************************************************/
    public function GetAccumulatedClusterSize()
    {
        $result = array();
        $sum    = 0;

        foreach ( $this->cluster as $cluster )
        {
            $sum += count( $cluster );

            $result[] = $sum;
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Split( $codecs )
    {
        $sum = 0;

        foreach ( $this->cluster as $length => $cluster )
        {
            $sum += count( $cluster );

            if ( ( $sum >= $codecs ) && ( ( $sum % $codecs ) == 0 ) )
            {
                break;
            }
        }

        $fileName  = reset( reset( $this->cluster ) );
        $itemName  = substr( $fileName, 0, $length );
        $codecName = substr( $fileName, $length );

        return array( $itemName, $codecName );
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
        $this->clusterSize[] = $clusterSize;
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
        $this->RenderClusterSize( $sink, $this->clusterSize[ 0 ] );
        $this->RenderClusterSize( $sink, $this->clusterSize[ 1 ] );
        $this->RenderCodecCount( $sink );

        $sink->Write( '<div class="clearer"></div>' );

        if ( $this->text != '' )
        {
            $this->RenderTextLog( $sink );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderClusterSize( $sink, $clusterSize )
    {
        $max = ceil( max( $clusterSize ) / 10 ) * 10;
        $chart[] = 'chs=400x200';
        $chart[] = 'cht=bvs';
        $chart[] = 'chd=t:' . implode( ',', $clusterSize );
        $chart[] = "chds=0,$max";
        $chart[] = 'chco=4D89F9';
        $chart[] = 'chxt=x,y';
        $chart[] = "chxr=1,0,$max";
        $chart[] = 'chxl=0:|' . implode( '|', array_keys( $clusterSize ) );
        $chart[] = 'chm=N,FFFFFF,0,,9,,c';

        $image = '<img src="http://chart.apis.google.com/chart?' . implode( '&amp;', $chart ) . '" />';

        $sink->OpenReportBlock( 'Cluster size distribution', 'chart' );
        $sink->Write( $image );
        $sink->CloseReportBlock();
    }

    /***************************************************************************
    ***************************************************************************/
    private function RenderCodecCount( $sink )
    {
        static $palette = array( '4D89F9', 'FFCEB4', 'BEF3A9', '96DEE4', 'DEB3FF', 'FF94C1', 'DDDB4A', '22C778', 'A6C7E3' );

        ksort( $this->codecCount );

        $snapshots = count( $this->label );
        $max       = ceil( $this->GetMaxCodecCountWight() + 0.5 );
        $color     = array();

        for ( $i = 0; $i < $snapshots; $i++ )
        {
            $series = array();

            foreach ( $this->codecCount as $weight )
            {
                $series[] = sprintf( "%.3f", $weight[ $i ] );
            }

            $data[] = implode( ',', $series );

            if ( $this->label[ $i ] == 'ApplyCodecCountProbability' )
            {
                $color[] = 'CC0000';
            }
            else
            {
                $color[] = $palette[ $i ];
            }
        }

        $chart[] = 'chs=400x200';
        $chart[] = 'cht=lc';
        $chart[] = 'chd=t:' . implode( '|', $data );
        $chart[] = "chds=0,$max";
        $chart[] = 'chco=' . implode( ',', $color );
        $chart[] = 'chxt=x,y';
        $chart[] = "chxr=1,0,$max";
        $chart[] = 'chxl=0:|' . implode( '|', array_keys( $this->codecCount ) );

        $image = '<img src="http://chart.apis.google.com/chart?' . implode( '&amp;', $chart ) . '" />';

        $sink->OpenReportBlock( 'Codecs number probability distribution', 'chart' );
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
