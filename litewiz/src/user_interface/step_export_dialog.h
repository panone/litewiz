/*******************************************************************************
*******************************************************************************/

#ifndef STEP_EXPORT_DIALOG_H
#define STEP_EXPORT_DIALOG_H

/******************************************************************************/

#include "export_dialog.h"

/******************************************************************************/

namespace Ui
{
    class StepExportDialog;
}

/*******************************************************************************
*******************************************************************************/
class StepExportDialog : public ExportDialog
{
    Q_OBJECT

    public:

        explicit StepExportDialog
        (
            Session * const session,
            QWidget * const parent = 0
        );

        virtual ~StepExportDialog
        (
            void
        );

    private slots:

        void setSessionType
        (
            int const type
        );

    private:

        virtual QString getSettingsName
        (
            void
        );

        virtual BrowseInfo getBrowseInfo
        (
            void
        );

        virtual void connectSignals
        (
            void
        );

        virtual void saveState
        (
            QSettings * const settings
        );

        virtual void restoreState
        (
            QSettings const & settings
        );

        virtual void saveSession
        (
            void
        );

    private:

        Ui::StepExportDialog * ui;
};

/******************************************************************************/

#endif /* STEP_EXPORT_DIALOG_H */
