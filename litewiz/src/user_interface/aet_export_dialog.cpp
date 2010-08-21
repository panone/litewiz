/*******************************************************************************
*******************************************************************************/

#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include "aet_session.h"
#include "export_dialog.h"
#include "aet_export_dialog.h"
#include "ui_aet_export_dialog.h"

/*******************************************************************************
*******************************************************************************/
AetExportDialog::AetExportDialog
(
    Session * const session,
    QWidget * const parent
) :
    ExportDialog( session, parent )
{
    ui = new Ui::AetExportDialog;

    ui->setupUi( this );
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
QString AetExportDialog::getSettingsName
(
    void
)
{
    return "AetExport";
}

/*******************************************************************************
*******************************************************************************/
ExportDialog::BrowseInfo AetExportDialog::getBrowseInfo
(
    void
)
{
    return ExportDialog::BrowseInfo
    (
        tr( "Save AET session" ),
        tr( "AET Sessions (*.aets);;All files (*.*)" )
    );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::connectSignals
(
    void
)
{
    initializeFilePicker( ui->fileNameEdit, ui->browseButton );

    ExportDialog::connectSignals();
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::saveState
(
    QSettings * const settings
)
{
    settings->setValue( "ListeningTest", ui->listeningTestCheckBox->isChecked() );
    settings->setValue( "RangeSelect", ui->rangeSelectCheckBox->isChecked() );
    settings->setValue( "RecentFileNames", ui->fileNameEdit->getHistory() );
    settings->setValue( "RecentTitles", ui->sectionTitleEdit->getHistory() );
    settings->setValue( "RecentAudioDevices", ui->audioDeviceEdit->getHistory() );
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::restoreState
(
    QSettings const & settings
)
{
    ui->listeningTestCheckBox->setChecked( settings.value( "ListeningTest" ).toBool() );
    ui->rangeSelectCheckBox->setChecked( settings.value( "RangeSelect" ).toBool() );
    ui->fileNameEdit->setHistory( settings.value( "RecentFileNames" ).toStringList() );
    ui->sectionTitleEdit->setHistory( settings.value( "RecentTitles" ).toStringList() );
    ui->audioDeviceEdit->setHistory( settings.value( "RecentAudioDevices" ).toStringList() );

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

/******************************************************************************/
