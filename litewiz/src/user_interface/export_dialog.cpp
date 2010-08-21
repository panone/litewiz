/*******************************************************************************
*******************************************************************************/

#include <QDialog>
#include <QFileDialog>
#include <QIcon>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QTimer>
#include "history_combo_box.h"
#include "export_dialog.h"

/*******************************************************************************
*******************************************************************************/
ExportDialog::BrowseInfo::BrowseInfo
(
    QString const & caption,
    QString const & pattern
) :
    caption( caption ),
    pattern( pattern )
{
}

/*******************************************************************************
*******************************************************************************/
ExportDialog::ExportDialog
(
    Session * const session,
    QWidget * const parent
) :
    QDialog( parent ),
    session( session )
{
    fileNameEdit       = 0;
    overwriteConfirmed = false;

    QTimer::singleShot( 0, this, SLOT( initialize() ) );
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::initializeFilePicker
(
    HistoryComboBox * const fileNameEdit,
    QPushButton     * const browseButton
)
{
    this->fileNameEdit = fileNameEdit;

    connect( browseButton, SIGNAL( clicked() ), this, SLOT( browse() ) );
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::saveState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( getSettingsName() );

    saveState( &settings );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::restoreState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( getSettingsName() );

    restoreState( settings );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
bool ExportDialog::confirmOverwrite
(
    QString const & fileName
)
{
    bool result = true;

    QFileInfo fileInfo( fileName );

    if ( fileInfo.exists() )
    {
        BrowseInfo info = getBrowseInfo();

        QMessageBox::StandardButton answer = QMessageBox::warning
        (
            this,
            info.caption,
            tr( "%1 already exists.\nDo you want to replace it?" ).arg( fileName ),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No
        );

        result = ( answer == QMessageBox::Yes );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::initialize
(
    void
)
{
    connectSignals();
    restoreGeometry();
    restoreState();
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::browse
(
    void
)
{
    BrowseInfo info = getBrowseInfo();

    QString fileName = QFileDialog::getSaveFileName( this, info.caption, QString(), info.pattern );

    if ( !fileName.isEmpty() )
    {
        fileNameEdit->lineEdit()->setText( fileName );

        overwriteConfirmed = true;
        confirmedFileName  = fileName;
    }
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::finalize
(
    int result
)
{
    saveGeometry();
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::accept
(
    void
)
{
    bool accept = true;

    if ( !overwriteConfirmed || ( confirmedFileName != fileNameEdit->lineEdit()->text() ) )
    {
        accept = confirmOverwrite( fileNameEdit->lineEdit()->text() );
    }

    if ( accept )
    {
        saveSession();
        saveState();

        QDialog::accept();
    }
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::connectSignals
(
    void
)
{
    connect( this, SIGNAL( finished( int ) ), this, SLOT( finalize( int ) ) );
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::saveGeometry
(
    void
)
{
    QString name = QString( "Geometry/%1Dialog" ).arg( getSettingsName() );

    QSettings().setValue( name, QDialog::saveGeometry() );
}

/*******************************************************************************
*******************************************************************************/
void ExportDialog::restoreGeometry
(
    void
)
{
    QString name = QString( "Geometry/%1Dialog" ).arg( getSettingsName() );

    QDialog::restoreGeometry( QSettings().value( name ).toByteArray() );
}

/******************************************************************************/
