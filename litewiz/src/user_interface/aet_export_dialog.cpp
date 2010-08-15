/*******************************************************************************
*******************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include "aet_session.h"
#include "aet_export_dialog.h"
#include "ui_aet_export_dialog.h"

/*******************************************************************************
*******************************************************************************/
AetExportDialog::AetExportDialog
(
    Session * const session,
    QWidget * const parent
) :
    QDialog( parent ),
    session( session )
{
    ui = new Ui::AetExportDialog;

    ui->setupUi( this );

    connectSignals();
    restoreGeometry();
    restoreState();
}

/*******************************************************************************
*******************************************************************************/
AetExportDialog::~AetExportDialog
(
    void
)
{
    delete ui;
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::connectSignals
(
    void
)
{
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( this, SIGNAL( finished( int ) ), this, SLOT( finalize( int ) ) );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::saveGeometry
(
    void
)
{
    QSettings().setValue( "Geometry/AetExportDialog", QDialog::saveGeometry() );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::restoreGeometry
(
    void
)
{
    QDialog::restoreGeometry( QSettings().value( "Geometry/AetExportDialog" ).toByteArray() );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::saveState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "AetExport" );

    settings.setValue( "ListeningTest", ui->listeningTestCheckBox->isChecked() );
    settings.setValue( "RangeSelect", ui->rangeSelectCheckBox->isChecked() );
    settings.setValue( "RecentFileNames", ui->fileNameEdit->getHistory() );
    settings.setValue( "RecentTitles", ui->sectionTitleEdit->getHistory() );
    settings.setValue( "RecentAudioDevices", ui->audioDeviceEdit->getHistory() );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::restoreState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "AetExport" );

    ui->listeningTestCheckBox->setChecked( settings.value( "ListeningTest" ).toBool() );
    ui->rangeSelectCheckBox->setChecked( settings.value( "RangeSelect" ).toBool() );
    ui->fileNameEdit->setHistory( settings.value( "RecentFileNames" ).toStringList() );
    ui->sectionTitleEdit->setHistory( settings.value( "RecentTitles" ).toStringList() );
    ui->audioDeviceEdit->setHistory( settings.value( "RecentAudioDevices" ).toStringList() );

    settings.endGroup();

    ui->fileNameEdit->setCurrentIndex( -1 );
    ui->sectionTitleEdit->setCurrentIndex( -1 );
    ui->audioDeviceEdit->setCurrentIndex( -1 );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::saveSession
(
    void
)
{
    AetSession aetSession( session );

    aetSession.setTitle( ui->sectionTitleEdit->lineEdit()->text() );
    aetSession.setAudioDevice( ui->audioDeviceEdit->lineEdit()->text() );

    QString fileName = ui->fileNameEdit->lineEdit()->text();

    if ( !aetSession.save( fileName ) )
    {
        QMessageBox::critical
        (
            this,
            tr( "AET Export" ),
            tr( "Failed to save file '%1'." ).arg( fileName )
        );
    }
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::browse
(
    void
)
{
    QString fileName = QFileDialog::getSaveFileName
    (
        this, tr("Save AET session"),
        QString(),
        tr( "AET Sessions (*.aets);;All files (*.*)" )
    );

    if ( !fileName.isEmpty() )
    {
        ui->fileNameEdit->lineEdit()->setText( fileName );
    }
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::finalize
(
    int result
)
{
    saveGeometry();
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::accept
(
    void
)
{
    saveSession();
    saveState();

    QDialog::accept();
}

/******************************************************************************/
