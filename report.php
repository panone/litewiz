<?php

/*******************************************************************************
*******************************************************************************/
class Report
{
    private $html;
    private $templateDir;
    private $itemName;
    private $codecName;
    private $log;

    /***************************************************************************
    ***************************************************************************/
    public function __construct( $templateDir )
    {
        if ( !file_exists( $templateDir . '/main.html' ) )
        {
            throw new Exception( 'Invalid report template directory' );
        }

        $this->templateDir = $templateDir;
        $this->html        = '';
    }

    /***************************************************************************
    ***************************************************************************/
    public function Write( $html )
    {
        $this->html .= $html . "\n";
    }

    /***************************************************************************
    ***************************************************************************/
    public function OpenTestCase( $testCase )
    {
        $fileName = '<span class="file-name">' . $testCase[ 'fileName' ] . '</span>';
        $items    = $testCase[ 'items' ] . ' item' . ( $testCase[ 'items' ] > 1 ) ? 's' : '';
        $codecs   = $testCase[ 'codecs' ] . ' codec' . ( $testCase[ 'codecs' ] > 1 ) ? 's' : '';

        $this->Write( '<div class="test-case">' );
        $this->Write( "<h2>$fileName ($items, $codecs)</h2>" );
    }

    /***************************************************************************
    ***************************************************************************/
    public function CloseTestCase()
    {
        $this->Write( '</div>' );
    }

    /***************************************************************************
    ***************************************************************************/
    public function Save( $fileName )
    {
        $template = file_get_contents( $this->templateDir . '/main.html' );
        $style    = $this->GetGlobFileContents( '*.css' );
        $script   = $this->GetGlobFileContents( '*.js' );

        $template = str_replace( '/* css placeholder */', $style, $template );
        $template = str_replace( '// js placeholder', $script, $template );
        $template = str_replace( '<!-- html placeholder -->', $this->html, $template );

        file_put_contents( $fileName, $template );
    }

    /***************************************************************************
    ***************************************************************************/
    private function GetGlobFileContents( $pattern )
    {
        $result = '';

        foreach ( glob($this->templateDir . '/' . $pattern ) as $fileName )
        {
            $result = file_get_contents( $fileName ) . "\n\n";
        }

        return $result;
    }
}
