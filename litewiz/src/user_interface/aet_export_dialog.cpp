/*******************************************************************************
*******************************************************************************/

#include <QDialog>
#include <QLineEdit>
#include <QSettings>
#include <algorithm>
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
    settings.setValue( "RecentFileNames", getComboBoxItems( ui->fileNameEdit ) );
    settings.setValue( "RecentTitles", getComboBoxItems( ui->sectionTitleEdit ) );
    settings.setValue( "RecentAudioDevices", getComboBoxItems( ui->audioDeviceEdit ) );

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
    ui->fileNameEdit->insertItems( 0, settings.value( "RecentFileNames" ).toStringList() );
    ui->sectionTitleEdit->insertItems( 0, settings.value( "RecentTitles" ).toStringList() );
    ui->audioDeviceEdit->insertItems( 0, settings.value( "RecentAudioDevices" ).toStringList() );

    settings.endGroup();

    ui->fileNameEdit->setCurrentIndex( -1 );
    ui->sectionTitleEdit->setCurrentIndex( -1 );
    ui->audioDeviceEdit->setCurrentIndex( -1 );
}

/*******************************************************************************
*******************************************************************************/
QStringList AetExportDialog::getComboBoxItems
(
    QComboBox const * const comboBox
)
{
    QLineEdit   * lineEdit = comboBox->lineEdit();
    QStringList   result;

    if ( ( lineEdit != 0 ) && !lineEdit->text().isEmpty() )
    {
        result.append( lineEdit->text() );
    }

    int count = std::min( comboBox->count(), 15 );

    for ( int i = 0; i < count; i++ )
    {
        result.append( comboBox->itemText( i ) );
    }

    result.removeDuplicates();

    return result;
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
