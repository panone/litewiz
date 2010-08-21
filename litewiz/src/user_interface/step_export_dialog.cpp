/*******************************************************************************
*******************************************************************************/

#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include "session.h"
#include "step_session.h"
#include "export_dialog.h"
#include "step_export_dialog.h"
#include "ui_step_export_dialog.h"

/*******************************************************************************
*******************************************************************************/
StepExportDialog::StepExportDialog
(
    Session * const session,
    QWidget * const parent
) :
    ExportDialog( session, parent )
{
    ui = new Ui::StepExportDialog;

    ui->setupUi( this );
}

/*******************************************************************************
*******************************************************************************/
StepExportDialog::~StepExportDialog()
{
    delete ui;
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::setSessionType
(
    int const type
)
{
    ui->sessionTypeCombo->setCurrentIndex( type );

    if ( ( type == StepSession::AbSession ) && ( session->getCurrentVariance() != 2 ) )
    {
        ui->warningLabel->setVisible( true );

        if ( session->getCurrentVariance() < 2 )
        {
            ui->warningLabel->setToolTip( tr( "There should be at least two variants." ) );
        }
        else
        {
            ui->warningLabel->setToolTip( tr( "Only first two variants will be saved." ) );
        }
    }
    else
    {
        ui->warningLabel->setVisible( false );
    }

    ui->hiddenReferenceCheckBox->setEnabled( type == StepSession::MushraSession );
}

/*******************************************************************************
*******************************************************************************/
QString StepExportDialog::getSettingsName
(
    void
)
{
    return "StepExport";
}

/*******************************************************************************
*******************************************************************************/
ExportDialog::BrowseInfo StepExportDialog::getBrowseInfo
(
    void
)
{
    return ExportDialog::BrowseInfo
    (
        tr( "Save STEP session" ),
        tr( "STEP Sessions (*.asi);;All files (*.*)" )
    );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::connectSignals
(
    void
)
{
    initializeFilePicker( ui->fileNameEdit, ui->browseButton );

    connect( ui->sessionTypeCombo, SIGNAL( currentIndexChanged( int ) ), this, SLOT( setSessionType( int ) ) );

    ExportDialog::connectSignals();
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::saveState
(
    QSettings * const settings
)
{
    settings->setValue( "RecentFileNames", ui->fileNameEdit->getHistory() );
    settings->setValue( "SessionType", ui->sessionTypeCombo->currentIndex() );
    settings->setValue( "HiddenReference", ui->hiddenReferenceCheckBox->isChecked() );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::restoreState
(
    QSettings const & settings
)
{
    setSessionType( settings.value( "SessionType" ).toInt() );

    ui->fileNameEdit->setHistory( settings.value( "RecentFileNames" ).toStringList() );
    ui->hiddenReferenceCheckBox->setChecked( settings.value( "HiddenReference" ).toBool() );

    ui->fileNameEdit->setCurrentIndex( -1 );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::saveSession
(
    void
)
{
    StepSession stepSession( session );

    stepSession.setType( ui->sessionTypeCombo->currentIndex() );
    stepSession.addHiddenReference( ui->hiddenReferenceCheckBox->isChecked() );

    QString fileName = ui->fileNameEdit->lineEdit()->text();

    if ( !stepSession.save( fileName ) )
    {
        QMessageBox::critical
        (
            this,
            tr( "STEP Export" ),
            tr( "Failed to save file '%1'." ).arg( fileName )
        );
    }
}

/******************************************************************************/
