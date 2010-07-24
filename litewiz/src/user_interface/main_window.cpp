/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QFileDialog>
#include <QSettings>
#include "utility.h"
#include "session.h"
#include "file_tree_model.h"
#include "item_list_model.h"
#include "variant_list_model.h"
#include "aet_export_dialog.h"
#include "ui_main_window.h"
#include "main_window.h"

/*******************************************************************************
*******************************************************************************/
MainWindow::MainWindow
(
    QWidget * parent
) :
    QMainWindow( parent )
{
    ui      = new Ui::MainWindow();
    session = new Session( this );

    setupUi();
    connectSignals();
    restoreGeometry();

    if ( QApplication::instance()->arguments().count() > 1 )
    {
        session->loadFileList( QApplication::instance()->arguments().at( 1 ) );
    }
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
void MainWindow::setupUi
(
    void
)
{
    ui->setupUi( this );

    fileTreeModel = new FileTreeModel( session, this );

    ui->fileTreeView->setModel( fileTreeModel );

    itemListModel = new ItemListModel( session, this );

    ui->itemListView->setModel( itemListModel );

    variantListModel = new VariantListModel( session, this );

    ui->variantListView->setModel( variantListModel );
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::connectSignals
(
    void
)
{
    connect( ui->addFilesAction, SIGNAL( triggered() ), this, SLOT( addFiles() ) );
    connect( ui->addDirectoryAction, SIGNAL( triggered() ), this, SLOT( addDirectory() ) );
    connect( ui->aetExportAction, SIGNAL( triggered() ), this, SLOT( exportAetSession() ) );

    connect( ui->itemListView, SIGNAL( excludeRequest( QIntList, bool ) ), session, SLOT( excludeItems( QIntList, bool ) ) );
    connect( ui->itemListView, SIGNAL( contextMenuRequest( ContextMenuInfo * const ) ), itemListModel, SLOT( initContextMenu( ContextMenuInfo * const ) ) );

    connect( ui->variantListView, SIGNAL( excludeRequest( QIntList, bool ) ), session, SLOT( excludeVariants( QIntList, bool ) ) );
    connect( ui->variantListView, SIGNAL( contextMenuRequest( ContextMenuInfo * const ) ), variantListModel, SLOT( initContextMenu( ContextMenuInfo * const ) ) );
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::saveGeometry
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "Geometry" );

    settings.setValue( "MainWindow", QMainWindow::saveGeometry() );
    settings.setValue( "Splitter1", ui->splitter1->saveState() );
    settings.setValue( "Splitter2", ui->splitter2->saveState() );
    settings.setValue( "FileTreeView", ui->fileTreeView->header()->saveState() );

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

    settings.beginGroup( "Geometry" );

    QMainWindow::restoreGeometry( settings.value( "MainWindow" ).toByteArray() );
    ui->splitter1->restoreState( settings.value( "Splitter1" ).toByteArray() );
    ui->splitter2->restoreState( settings.value( "Splitter2" ).toByteArray() );
    ui->fileTreeView->header()->restoreState( settings.value( "FileTreeView" ).toByteArray() );

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
void MainWindow::exportAetSession
(
    void
)
{
    AetExportDialog dialog( session, this );

    dialog.exec();
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
