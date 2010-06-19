<?php

/*******************************************************************************
*******************************************************************************/
class CommandLineArgument
{
    private $switch;
    private $type;
    private $optional;
    private $multiple;
    private $set;
    private $default;
    private $name;
    private $caption;
    private $comment;

    private $value;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $definition )
    {
        $this->switch   = '';
        $this->type     = 'string';
        $this->optional = FALSE;
        $this->multiple = FALSE;
        $this->set      = array();
        $this->default  = '';
        $this->name     = '';
        $this->caption  = '';
        $this->comment  = '';

        $this->value    = '';

        $this->Initialize( $definition );
    }

    /***************************************************************************
    ***************************************************************************/
    private function SetProperty( $name, $value )
    {
        switch ( $name )
        {
            case 'switch':
            case 'type':
            case 'default':
            case 'name':
            case 'caption':
                eval( '$this->' . $name . '= $value;' );
                break;

            case 'optional':
            case 'multiple':
                $true  = array( 'yes', 'on', 'true', '1' );
                $value = in_array( $value, $true );

                eval( '$this->' . $name . '= $value;' );
                break;

            case 'set':
                $value = explode( ',', $value );

                foreach ( $value as $line )
                {
                    $this->set[] = trim( $line );
                }
                break;

            case 'comment':
                $value = preg_replace( "/(\"|')(.*?)(?<!\\\\)\\1/", '$2', $value );
                $value = preg_replace( "/\\\\(\"|')/", '$1', $value );

                // properties are in reverse order

                if ( $this->comment != '' )
                {
                    $this->comment = "\n" . $this->comment;
                }

                $this->comment = $value . $this->comment;
                break;

            default:
                break;
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function InitDefaults()
    {
        if ( $this->name == '' )
        {
            $this->name = $this->switch;
        }

        if ( $this->switch == '' )
        {
            $this->switch = $this->name;
        }

        if ( $this->caption == '' )
        {
            $this->caption = $this->name;
        }

        if ( $this->multiple )
        {
            $this->value = array();
        }

        if ( $this->optional )
        {
            $this->AddValue( $this->default );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function CheckProperties( $definition )
    {
        if ( $this->switch == '' )
        {
            throw new Exception( 'Failed to initialize command line argument "' . $definition . '"' );
        }

        if ( ( $this->type == 'switch' ) && ( count( $this->set ) == 0 ) )
        {
            throw new Exception( 'Missing a set of values for command line switch "' . $definition . '"' );
        }

        $type = array( 'string', 'integer', 'float', 'switch' );

        if ( !in_array( $this->type, $type ) )
        {
            throw new Exception( 'Invalid type of command line argument "' . $definition . '"' );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function Initialize( $definition )
    {
        // reverse properties order to handle false semicolon splits
        $temp = array_reverse( explode( ';', $definition ) );
        $tail = '';

        foreach ( $temp as $line )
        {
            if ( preg_match( "/([\w-]+)\s*:\s*(.+?)\s*$/", $line, $match ) == 1 )
            {
                $this->SetProperty( $match[ 1 ], $match[ 2 ] . $tail );

                $tail = '';
            }
            else
            {
                if ( $line != '' )
                {
                    // fix false splits
                    $tail = ';' . $line . $tail;
                }
            }
        }

        $this->InitDefaults();

        $this->CheckProperties( $definition );
    }

    /***************************************************************************
    ***************************************************************************/
    public function PrintHelp()
    {
        print( '  -'  . $this->switch );

        if ( $this->type == 'switch' )
        {
            print( ' {' );

            print( $this->set[ 0 ] );

            for ( $i = 1; $i < count( $this->set ); $i++ )
            {
                print( '|' . $this->set[ $i ] );
            }

            print( '}' );
        }
        else
        {
            print( ' <' . $this->type . '>' );
        }

        print( "\n" );

        if ( $this->comment != '' )
        {
            $temp = explode( "\n", $this->comment );

            for ( $i = 0; $i < count( $temp ); $i++ )
            {
                print( '    ' . $temp[ $i ] . "\n" );
            }
        }
        else
        {
            print( '    ' . $this->caption . ".\n" );
        }

        if ( $this->optional )
        {
            print( '    Default: ' . $this->default . "\n" );
        }

        print( "\n" );
    }

    /***************************************************************************
    ***************************************************************************/
    public function IsOptional()
    {
        return $this->optional;
    }

    /***************************************************************************
    ***************************************************************************/
    public function GetCaptionLength()
    {
        return strlen( $this->caption );
    }

    /***************************************************************************
    ***************************************************************************/
    public function GetName()
    {
        return $this->name;
    }

    /***************************************************************************
    ***************************************************************************/
    public function CheckName( $name )
    {
        return ( $name == $this->switch );
    }

    /***************************************************************************
    ***************************************************************************/
    public function AddValue( $value )
    {
        switch ( $this->type )
        {
            case 'string':
                break;

            case 'integer':
                $value = intval( $value );
                break;

            case 'float':
                $value = floatval( $value );
                break;

            case 'switch':
                if ( !in_array( $value, $this->set ) )
                {
                    throw new Exception( 'Value "' . $value . '" is invalid for the argument "-' . $this->switch . '"' );
                }
                break;

            default:
                break;
        }

        if ( $this->multiple )
        {
            $this->value[] = $value;
        }
        else
        {
            $this->value = $value;
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function SetDefault()
    {
    }

    /***************************************************************************
    ***************************************************************************/
    public function Validate()
    {
        if ( !$this->optional )
        {
            $failed = FALSE;

            if ( $this->multiple )
            {
                $failed = ( count( $this->value ) == 0 );
            }
            else
            {
                $failed = ( $this->value == '' );
            }

            if ( $failed )
            {
                throw new Exception( 'Value for obligatory parameter "-' . $this->switch . '" was not specified.' );
            }
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function PrintValue( $captionWidth )
    {
        print( str_pad( $this->caption, $captionWidth ) . ' : ' );

        if ( $this->multiple )
        {
            print( $this->value[ 0 ] . "\n" );

            for ( $i = 1; $i < count( $this->value ); $i++ )
            {
                print( str_pad( '', $captionWidth + 3 ) . $this->value[ $i ] . "\n" );
            }
        }
        else
        {
            print( $this->value . "\n" );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function GetValue()
    {
        return $this->value;
    }
}

/*******************************************************************************
*******************************************************************************/
class CommandLineParser
{
    private $info;
    private $argument;
    private $printValues;
    private $example;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $printValues = TRUE )
    {
        $this->info        = '';
        $this->argument    = array();
        $this->printValues = $printValues;
        $this->example     = array();
    }

    /***************************************************************************
    ***************************************************************************/
    public function AddInfo( $info )
    {
        $this->info .= $info;
    }

    /***************************************************************************
    ***************************************************************************/
    public function AddArgument( $definition )
    {
        $this->argument[] = new CommandLineArgument( $definition );
    }

    /***************************************************************************
    ***************************************************************************/
    public function AddExample( $example )
    {
        $this->example[] = $example;
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetObligatoryCount()
    {
        $result = 0;

        foreach ( $this->argument as $argument )
        {
            if ( !$argument->IsOptional() )
            {
                $result++;
            }
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetOptionalCount()
    {
        $result = 0;

        foreach ( $this->argument as $argument )
        {
            if ( $argument->IsOptional() )
            {
                $result++;
            }
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    private function PrintHelp( $appName )
    {
        print( "\n" );

        if ( $this->info != '' )
        {
            print( $this->info );
            print( "\n\n" );
        }

        print( "Usage:\n" );
        print( '  ' . $appName . " <arguments>\n\n" );

        print( "Obligatory arguments:\n\n" );

        if ( $this->GetObligatoryCount() > 0 )
        {
            foreach ( $this->argument as $argument )
            {
                if ( !$argument->IsOptional() )
                {
                    $argument->PrintHelp();
                }
            }
        }
        else
        {
            print( "  <none>\n\n" );
        }

        print( "Optional arguments:\n\n" );

        if ( $this->GetOptionalCount() > 0 )
        {
            foreach ( $this->argument as $argument )
            {
                if ( $argument->IsOptional() )
                {
                    $argument->PrintHelp();
                }
            }
        }
        else
        {
            print( "  <none>\n\n" );
        }

        $count = count( $this->example );

        if ( $count > 0 )
        {
            print( 'Example' . ( ( $count == 1 )? '': 's' ) . ":\n\n" );

            foreach ( $this->example as $example )
            {
                print( $appName . ' ' . $example . "\n\n" );
            }
        }
    }

    /***************************************************************************
    ***************************************************************************/
    private function PrintValues()
    {
        $captionWidth = 0;

        foreach ( $this->argument as $argument )
        {
            $temp = $argument->GetCaptionLength();

            if ( $captionWidth < $temp )
            {
                $captionWidth = $temp;
            }
        }

        print( "\n" );

        foreach ( $this->argument as $argument )
        {
            $temp = $argument->PrintValue( $captionWidth );
        }

        print( "\n" );
    }

    /***************************************************************************
    ***************************************************************************/
    private function ParseArguments( $count )
    {
        global $argv;

        for ( $i = 1; $i < $count; $i++ )
        {
            $name  = ltrim( $argv[ $i ], '/-' );
            $found = FALSE;

            foreach ( $this->argument as $argument )
            {
                $found = $argument->CheckName( $name );

                if ( $found )
                {
                    $argument->AddValue( $argv[ ++$i ] );
                    break;
                }
            }

            if ( !$found )
            {
                throw new Exception( 'Unknown command line argument "' . $argv[ $i ] . "\"\n" );
            }
        }

        foreach ( $this->argument as $argument )
        {
            $argument->SetDefault();
        }

        if ( $this->printValues )
        {
            $this->PrintValues();
        }

        foreach ( $this->argument as $argument )
        {
            $argument->Validate();
        }

        $result = array();

        foreach ( $this->argument as $argument )
        {
            $result[ $argument->GetName() ] = $argument->GetValue();
        }

        return $result;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Parse()
    {
        global $argc;
        global $argv;

        $count  = $argc;

        while ( $argv[ $count - 1 ] == '' )
        {
            $count--;
        }

        while ( ( $count > 1 ) && ( $argv[ $count - 1 ] == $argv[ $count - 2 ] ) )
        {
            $count--;
        }

        $help      = array( '--help', '-help', '-h', '/h', '-?', '/?' );
        $printHelp = FALSE;

        if ( ( $count - 1 ) < $this->GetObligatoryCount() )
        {
            $printHelp = TRUE;
        }
        else
        {
            for ( $i = 1; $i < $count; $i++ )
            {
                if ( in_array( $argv[ $i ], $help ) )
                {
                    $printHelp = TRUE;
                    break;
                }
            }
        }

        $result = NULL;

        if ( $printHelp )
        {
            $this->PrintHelp( basename( $argv[ 0 ] ) );
        }
        else
        {
            $result = $this->ParseArguments( $count );
        }

        return $result;
    }
}

/*******************************************************************************
*******************************************************************************/
class ProgressReport
{
    private $style;
    private $session;
    private $progress;
    private $newLine;
    private $lastLen;
    private $numeric;
    private $lastWrap;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $style = '' )
    {
        $this->style[ 'numeric-width'     ] = 5;
        $this->style[ 'print-colon'       ] = TRUE;
        $this->style[ 'print-done'        ] = TRUE;
        $this->style[ 'print-numeric'     ] = TRUE;
        $this->style[ 'print-reports'     ] = TRUE;
        $this->style[ 'print-sessions'    ] = FALSE;
        $this->style[ 'print-title'       ] = TRUE;
        $this->style[ 'separate-sessions' ] = TRUE;
        $this->style[ 'width'             ] = 100;

        if ( $style != '' )
        {
            $this->SetStyle( $style );
        }

        $this->session  = 0;
        $this->progress = 0;
        $this->newLine  = FALSE;
        $this->lastLen  = 0;
        $this->numeric  = TRUE;
        $this->lastWrap = 0;
    }

    /***************************************************************************
    ***************************************************************************/
    private function SetOption( $name, $value )
    {
        switch ( $name )
        {
            case 'numeric-width':
                $value = max( intval( $value ), 1 );
                break;

            case 'print-colon':
            case 'print-done':
            case 'print-numeric':
            case 'print-reports':
            case 'print-sessions':
            case 'print-title':
            case 'separate-sessions':
                $true  = array( 'yes', 'on', 'true', '1' );
                $value = in_array( $value, $true );
                break;

            case 'width':
                $value = max( intval( $value ), 10 );
                break;

            default:
                $value = NULL;
                break;
        }

        if ( $value !== NULL )
        {
            $this->style[ $name ] = $value;
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function SetStyle( $style )
    {
        $style = explode( ';', $style );

        foreach ( $style as $line )
        {
            if ( preg_match( "/([\w-]+)\s*:\s*([\w-]+)/", $line, $match ) == 1 )
            {
                $this->SetOption( $match[ 1 ], $match[ 2 ] );
            }
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function Start( $caption )
    {
        if ( $this->style[ 'print-title' ] )
        {
            print( $caption );

            if ( $this->style[ 'print-colon' ] )
            {
                print( ':' );
            }

            print( "\n" );
        }

        $this->session++;
        $this->progress = 0;
        $this->newLine  = TRUE;
        $this->lastLen  = 0;
        $this->numeric  = TRUE;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Report( $message, $advance = TRUE )
    {
        $message = strval( $message );

        if ( $this->numeric )
        {
            if ( !$this->newLine )
            {
                print( "\n" );
            }

            if ( $this->style[ 'print-numeric' ] )
            {
                $numeric = '';

                if ( $this->style[ 'print-sessions' ] )
                {
                    $numeric .= $this->session;

                    if ( $this->style[ 'print-reports' ] )
                    {
                        $numeric .= '/';
                    }
                }

                if ( $this->style[ 'print-reports' ] )
                {
                    $numeric .= $this->progress;
                }

                print( '[' . str_pad( $numeric, $this->style[ 'numeric-width' ], ' ', STR_PAD_LEFT ) . ']' );
            }

            $this->newLine  = FALSE;
            $this->numeric  = FALSE;
            $this->lastWrap = $this->progress;
        }

        if ( $this->lastLen > 0 )
        {
            print( str_pad( '', 3 * $this->lastLen, "\010 \010" ) );
        }

        print( $message );

        if ( $advance )
        {
            $this->progress++;
            $this->lastLen = 0;

            if ( ( $this->progress - $this->lastWrap ) == $this->style[ 'width' ] )
            {
                $this->numeric = TRUE;
            }
        }
        else
        {
            $this->lastLen = strlen( $message );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public function Wrap()
    {
        $this->numeric = TRUE;
    }

    /***************************************************************************
    ***************************************************************************/
    public function Finish()
    {
        if ( !$this->newLine )
        {
            print( "\n" );
        }

        if ( $this->style[ 'print-done' ] )
        {
            print( "done.\n" );
        }

        if ( $this->style[ 'separate-sessions' ] )
        {
            print( "\n" );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
class LogFile
{
    private $file;
    private $newLine;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $fileName )
    {
        $this->file = @fopen( $fileName, 'wb' );

        if ( $this->file == NULL )
        {
            throw new Exception( 'Cannot open the log file "' . $fileName . '"' );
        }

        $this->newLine = TRUE;
    }

    /***************************************************************************
    ***************************************************************************/
    public function __destruct()
    {
        fclose( $this->file );
    }

    /***************************************************************************
    ***************************************************************************/
    public function __clone()
    {
        trigger_error( 'Clone is not allowed.', E_USER_ERROR );
    }

    /***************************************************************************
    ***************************************************************************/
    public function Log( $message )
    {
        fputs( $this->file, preg_replace( "/([^\r])\n/", "\\1\r\n", $message ) );

        $this->newLine = ( substr( $message, -1 ) == "\n" );
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogLine( $message )
    {
        $this->Log( $message . "\n" );
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogError( $message )
    {
        $this->ForceNewLine();
        $this->LogLine( 'Error: ' . $message );
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogException( $exception )
    {
        $this->LogError( $exception->getMessage() );
    }

    /***************************************************************************
    ***************************************************************************/
    public function LogLineDateTime( $message )
    {
        $this->LogLine( date( 'Y-m-d H:i:s : ' ) . $message );
    }

    /***************************************************************************
    ***************************************************************************/
    public function ForceNewLine()
    {
        if ( !$this->newLine )
        {
            $this->Log( "\n" );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
class LogSink
{
    private static $instance;

    private $logFile;

    /***************************************************************************
    ***************************************************************************/
    protected function __construct( $fileName )
    {
        $this->logFile = NULL;

        if ( $fileName != '<none>' )
        {
            $this->logFile = new LogFile( $fileName );
        }

        self::$instance = $this;
    }

    /***************************************************************************
    ***************************************************************************/
    public function __clone()
    {
        trigger_error( 'Clone is not allowed.', E_USER_ERROR );
    }

    /***************************************************************************
    ***************************************************************************/
    public static function Log( $message )
    {
        if ( ( self::$instance != NULL ) && ( self::$instance->logFile != NULL ) )
        {
            self::$instance->logFile->Log( $message );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public static function LogLine( $message )
    {
        if ( ( self::$instance != NULL ) && ( self::$instance->logFile != NULL ) )
        {
            self::$instance->logFile->LogLine( $message );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public static function LogError( $message )
    {
        if ( ( self::$instance != NULL ) && ( self::$instance->logFile != NULL ) )
        {
            self::$instance->logFile->LogError( $message );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public static function LogException( $exception )
    {
        if ( ( self::$instance != NULL ) && ( self::$instance->logFile != NULL ) )
        {
            self::$instance->logFile->LogException( $exception );
        }
    }

    /***************************************************************************
    ***************************************************************************/
    public static function LogLineDateTime( $message )
    {
        if ( ( self::$instance != NULL ) && ( self::$instance->logFile != NULL ) )
        {
            self::$instance->logFile->LogLineDateTime( $message );
        }
    }
}

/*******************************************************************************
*******************************************************************************/
abstract class BaseApplication extends LogSink
{
    protected $progress;

    /***************************************************************************
        Description:
            Definition of the command line options. Implementation of this
            method is optional.
    ***************************************************************************/
    //public abstract static function SetupCommandLine( $parser );

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $parameters )
    {
        $this->progress = new ProgressReport();

        parent::__construct( $parameters[ 'log' ] );

        $this->LogLineDateTime( 'Logging started' );
    }

    /***************************************************************************
    ***************************************************************************/
    public function __destruct()
    {
        $this->LogLineDateTime( 'Logging finished' );
    }

    /***************************************************************************
        Description:
            Main application processing
    ***************************************************************************/
    public abstract function Main();
}

/*******************************************************************************
*******************************************************************************/
class Executable
{
    /***************************************************************************
    ***************************************************************************/
    public static function Run( $className )
    {
        try
        {
            if ( !is_subclass_of( $className, 'BaseApplication' ) )
            {
                throw new Exception( 'Application class must derive from BaseApplication' );
            }

            $parser = new CommandLineParser();

            if ( in_array( 'SetupCommandLine', get_class_methods( $className ) ) )
            {
                eval( $className . '::SetupCommandLine( $parser );' );
            }

            $parser->AddArgument( 'switch: log; caption: Log file; optional: 1; default: <none>;' );

            $parameters = $parser->Parse();

            if ( $parameters != NULL )
            {
                $application = new $className( $parameters );

                $application->Main();
            }
        }
        catch ( Exception $error )
        {
            print( 'Error: ' . $error->getMessage() . "\n" );
        }
    }
}
