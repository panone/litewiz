/*******************************************************************************
*******************************************************************************/

#include <QSettings>
#include <QVariant>
#include "options_dialog.h"
#include "ui_options_dialog.h"

/*******************************************************************************
*******************************************************************************/
OptionsDialog::OptionsDialog
(
    QWidget * const parent
) :
    QDialog( parent )
{
    ui = new Ui::OptionsDialog;

    ui->setupUi( this );

    restoreState();
}

/*******************************************************************************
*******************************************************************************/
OptionsDialog::~OptionsDialog
(
    void
)
{
    delete ui;
}

/*******************************************************************************
*******************************************************************************/
void OptionsDialog::saveState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "Options" );

    settings.setValue( "AutoClassify", ui->autoClassifyRadioButton->isChecked() );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void OptionsDialog::restoreState
(
    void
)
{
    QSettings settings;

    settings.beginGroup( "Options" );

    bool autoClassify = settings.value( "AutoClassify", true ).toBool();

    ui->autoClassifyRadioButton->setChecked( autoClassify );
    ui->manualClassifyRadioButton->setChecked( !autoClassify );

    settings.endGroup();
}

/*******************************************************************************
*******************************************************************************/
void OptionsDialog::accept
(
    void
)
{
    saveState();

    QDialog::accept();
}

/******************************************************************************/
