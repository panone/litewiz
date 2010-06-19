<?php

include_once( 'application.php' );
include_once( 'classifier.php' );

/*******************************************************************************
*******************************************************************************/
class Application extends BaseApplication
{
    private $input;

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

        $this->input = $parameters[ 'input' ];
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetFileNames()
    {
        $temp   = file( $this->input );
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

    /***************************************************************************
    ***************************************************************************/
    public function Main()
    {
        $classifier = new Classifier();

        $classifier->Classify( $this->GetFileNames() );
    }
}

/******************************************************************************/

Executable::Run( 'Application' );
