/*******************************************************************************
*******************************************************************************/

#include <QDialog>
#include <QSettings>
#include "aet_export_dialog.h"
#include "ui_aet_export_dialog.h"

/*******************************************************************************
*******************************************************************************/
AetExportDialog::AetExportDialog
(
    QWidget * parent
) :
    QDialog( parent )
{
    ui = new Ui::AetExportDialog;

    ui->setupUi( this );

    connectSignals();
    restoreGeometry();
    restoreState();
}

/*******************************************************************************
*******************************************************************************/
void AetExportDialog::connectSignals
(
    void
)
{
    connect( this, SIGNAL( finished( int ) ), this, SLOT( finalize( int ) ) );
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

    settings.endGroup();
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
    saveState();

    QDialog::accept();
}

/******************************************************************************/
