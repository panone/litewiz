/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QFileDialog>
#include <QSettings>
#include "main_window.h"
#include "session.h"
#include "file_tree_model.h"
#include "ui_main_window.h"

/*******************************************************************************
*******************************************************************************/
MainWindow::MainWindow
(
    QWidget * parent
) :
    QMainWindow( parent )
{
    ui = new Ui::MainWindow();

    ui->setupUi( this );

    connect( ui->addFilesAction, SIGNAL( triggered() ), this, SLOT( addFiles() ) );
    connect( ui->addDirectoryAction, SIGNAL( triggered() ), this, SLOT( addDirectory() ) );

    restoreGeometry();

    session = new Session( this );

    if ( QApplication::instance()->arguments().count() > 1 )
    {
        session->loadFileList( QApplication::instance()->arguments().at( 1 ) );
    }

    fileTreeModel = new FileTreeModel( session, this );

    ui->fileTreeView->setModel( fileTreeModel );
    //ui->fileTreeView->setRootIsDecorated( false );
}

/*******************************************************************************
*******************************************************************************/
MainWindow::~MainWindow
(
    void
)
{
    delete ui;
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::saveGeometry
(
    void
)
{
    QSettings settings;

    settings.beginGroup("Geometry");

    settings.setValue( "MainWindow", QMainWindow::saveGeometry() );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::restoreGeometry
(
    void
)
{
    QSettings settings;

    settings.beginGroup("Geometry");

    QMainWindow::restoreGeometry( settings.value( "MainWindow" ).toByteArray() );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::addFiles
(
    void
)
{
    QStringList fileNames = QFileDialog::getOpenFileNames
    (
        this,
        QString(),
        QString(),
        tr( "Waveforms (*.wav);;All files (*.*)" )
    );

    if ( fileNames.count() > 0 )
    {
        session->addFiles( fileNames );
    }
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::addDirectory
(
    void
)
{
    QString directoryName =  QFileDialog::getExistingDirectory( this, tr( "Select a directory" ) );

    if ( !directoryName.isNull() )
    {
        session->addDirectory( directoryName );
    }
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::closeEvent
(
    QCloseEvent * event
)
{
    saveGeometry();

    QMainWindow::closeEvent( event );
}

/******************************************************************************/
