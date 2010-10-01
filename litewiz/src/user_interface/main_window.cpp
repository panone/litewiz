/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QFileDialog>
#include <QSettings>
#include "utility.h"
#include "session.h"
#include "file_collection.h"
#include "file_tree_model.h"
#include "item_list_model.h"
#include "variant_list_model.h"
#include "aet_export_dialog.h"
#include "step_export_dialog.h"
#include "options_dialog.h"
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
    connect( ui->fileMenu, SIGNAL( aboutToShow() ), this, SLOT( enableExport() ) );
    connect( ui->toolsMenu, SIGNAL( aboutToShow() ), this, SLOT( enableClassify() ) );

    connect( ui->addFilesAction, SIGNAL( triggered() ), this, SLOT( addFiles() ) );
    connect( ui->addDirectoryAction, SIGNAL( triggered() ), this, SLOT( addDirectory() ) );
    connect( ui->aetExportAction, SIGNAL( triggered() ), this, SLOT( exportAetSession() ) );
    connect( ui->stepExportAction, SIGNAL( triggered() ), this, SLOT( exportStepSession() ) );
    connect( ui->exitAction, SIGNAL( triggered() ), qApp, SLOT( quit() ) );

    connect( ui->classifyAction, SIGNAL( triggered() ), session, SLOT( classify() ) );
    connect( ui->optionsAction, SIGNAL( triggered() ), this, SLOT( showOptionsDialog() ) );

    connect( this, SIGNAL( settingsChanged() ), session, SLOT( loadSettings() ) );

    connect( itemListModel, SIGNAL( dataChanged( QModelIndex, QModelIndex ) ), this, SLOT( updateFileTreeView() ) );
    connect( variantListModel, SIGNAL( dataChanged( QModelIndex, QModelIndex ) ), this, SLOT( updateFileTreeView() ) );

    connect( ui->varianceSlider, SIGNAL( valueChanged( int ) ), session, SLOT( setCurrentVariance( int ) ) );

    connect( session, SIGNAL( classificationChanged() ), this, SLOT( updateVariance() ) );
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
void MainWindow::enableExport
(
    void
)
{
    ui->exportMenu->setEnabled( session->getFiles()->getIncludedCount() > 0 );
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::enableClassify
(
    void
)
{
    ui->classifyAction->setEnabled( session->getFiles()->getCount() > 0 );
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
    QSettings settings;

    QString directoryName =  QFileDialog::getExistingDirectory
    (
        this,
        tr( "Select a directory" ),
        settings.value( "LastSelectedDir" ).toString()
    );

    if ( !directoryName.isEmpty() )
    {
        settings.setValue( "LastSelectedDir", directoryName );

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
void MainWindow::exportStepSession
(
    void
)
{
    StepExportDialog dialog( session, this );

    dialog.exec();
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::showOptionsDialog
(
    void
)
{
    OptionsDialog dialog( this );

    if ( dialog.exec() == QDialog::Accepted )
    {
        emit settingsChanged();
    }
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::updateFileTreeView
(
    void
)
{
    //ui->fileTreeView->update();
    //ui->fileTreeView->repaint();
    ui->fileTreeView->doItemsLayout();
}

/*******************************************************************************
*******************************************************************************/
void MainWindow::updateVariance
(
    void
)
{
    int varianceCount   = session->getPossibleVariance().count();
    int currentVariance = session->getCurrentVariance();

    if ( varianceCount < 1 )
    {
        ui->varianceEdit->clear();
    }
    else
    {
        ui->varianceEdit->setText( QString( "%1" ).arg( currentVariance ) );
    }

    if ( varianceCount < 2 )
    {
        ui->varianceSlider->setRange( 0, 0 );
    }
    else
    {
        ui->varianceSlider->setRange( 0, varianceCount - 1 );
        ui->varianceSlider->setSliderPosition( session->getPossibleVariance().indexOf( currentVariance ) );
    }

    ui->varianceEdit->setEnabled( varianceCount > 0 );
    ui->varianceSlider->setEnabled( varianceCount > 1 );
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
