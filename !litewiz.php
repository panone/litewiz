<?php

include_once( 'spyc.php' );
include_once( 'application.php' );
include_once( 'classifier.php' );

/*******************************************************************************
*******************************************************************************/
class Application extends BaseApplication
{
    private $input;
    private $testSet;

    /***************************************************************************
    ***************************************************************************/
    public static function SetupCommandLine( $parser )
    {
        $arg  = 'switch   : i;';
        $arg .= 'optional : yes;';
        $arg .= 'name     : input;';
        $arg .= 'caption  : Input file;';
        $arg .= 'default  : #input.txt;';

        $parser->AddArgument( $arg );

        $arg  = 'switch   : ts;';
        $arg .= 'optional : yes;';
        $arg .= 'name     : test;';
        $arg .= 'caption  : Test set file;';
        $arg .= 'default  : <none>;';

        $parser->AddArgument( $arg );
    }

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $parameters )
    {
        if ( $parameters[ 'log' ] == '<none>' )
        {
            $parameters[ 'log' ] = '~log';
        }

        parent::__construct( $parameters );

        $this->testSet = ( $parameters[ 'test' ] != '<none>' );
        $this->input   = ( $this->testSet ) ? $parameters[ 'test' ] : $parameters[ 'input' ];
    }

    /***************************************************************************
    ***************************************************************************/
    public function Main()
    {
        if ( $this->testSet )
        {
            $this->RunTestSet( $this->input );
        }
        else
        {
            $classifier = new Classifier();

            $classifier->Classify( $this->GetFileNames( $this->input ) );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function RunTestSet( $input )
    {
        $classifier  = new Classifier();
        $testSet     = Spyc::YAMLLoad( $input );
        $testBaseDir = dirname( realpath( $input ) ) . '/';

        foreach ( $testSet as $case )
        {
            $fileName = $testBaseDir . $case[ 'fileName' ];

            $classifier->Classify( $this->GetFileNames( $fileName ) );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetFileNames( $input )
    {
        $temp   = file( $input );
        $result = array();

        foreach ( $temp as $line )
        {
            $line = trim( $line );

            if ( $line != '' )
            {
                $result[] = $line;
            }
        }

        return $result;
    }
}

/******************************************************************************/

Executable::Run( 'Application' );
