/*******************************************************************************
*******************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include "session.h"
#include "step_session.h"
#include "step_export_dialog.h"
#include "ui_step_export_dialog.h"

/*******************************************************************************
*******************************************************************************/
StepExportDialog::StepExportDialog
(
    Session * const session,
    QWidget * const parent
) :
    QDialog( parent ),
    session( session )
{
    ui = new Ui::StepExportDialog;

    ui->setupUi( this );

    connectSignals();
    restoreGeometry();
    restoreState();
}

/*******************************************************************************
*******************************************************************************/
StepExportDialog::~StepExportDialog()
{
    delete ui;
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::connectSignals
(
    void
)
{
    connect( ui->browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
    connect( ui->sessionTypeCombo, SIGNAL( currentIndexChanged( int ) ), this, SLOT( setSessionType( int ) ) );
    connect( this, SIGNAL( finished( int ) ), this, SLOT( finalize( int ) ) );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::saveGeometry
(
    void
)
{
    QSettings().setValue( "Geometry/StepExportDialog", QDialog::saveGeometry() );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::restoreGeometry
(
    void
)
{
    QDialog::restoreGeometry( QSettings().value( "Geometry/StepExportDialog" ).toByteArray() );
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::saveState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "StepExport" );

    settings.setValue( "RecentFileNames", ui->fileNameEdit->getHistory() );
    settings.setValue( "SessionType", ui->sessionTypeCombo->currentIndex() );
    settings.setValue( "HiddenReference", ui->hiddenReferenceCheckBox->isChecked() );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::restoreState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "StepExport" );

    setSessionType( settings.value( "SessionType" ).toInt() );

    ui->fileNameEdit->setHistory( settings.value( "RecentFileNames" ).toStringList() );
    ui->hiddenReferenceCheckBox->setChecked( settings.value( "HiddenReference" ).toBool() );

    settings.endGroup();

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

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::browse
(
    void
)
{
    QString fileName = QFileDialog::getSaveFileName
    (
        this,
        tr("Save STEP session"),
        QString(),
        tr( "STEP Sessions (*.asi);;All files (*.*)" )
    );

    if ( !fileName.isEmpty() )
    {
        ui->fileNameEdit->lineEdit()->setText( fileName );
    }
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
void StepExportDialog::finalize
(
    int result
)
{
    saveGeometry();
}

/*******************************************************************************
*******************************************************************************/
void StepExportDialog::accept
(
    void
)
{
    saveSession();
    saveState();

    QDialog::accept();
}

/******************************************************************************/
