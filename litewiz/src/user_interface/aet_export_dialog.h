/*******************************************************************************
*******************************************************************************/

#ifndef AET_EXPORT_DIALOG_H
#define AET_EXPORT_DIALOG_H

/******************************************************************************/

#include "export_dialog.h"

/******************************************************************************/

namespace Ui
{
    class AetExportDialog;
}

/*******************************************************************************
*******************************************************************************/
class AetExportDialog : public ExportDialog
{
    Q_OBJECT

    public:

        explicit AetExportDialog
        (
            Session * const session,
            QWidget * const parent = 0
        );

        virtual ~AetExportDialog
        (
            void
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

        Ui::AetExportDialog * ui;
};

/******************************************************************************/

#endif /* AET_EXPORT_DIALOG_H */
