/*******************************************************************************
*******************************************************************************/

#ifndef STEP_EXPORT_DIALOG_H
#define STEP_EXPORT_DIALOG_H

/******************************************************************************/

#include <QDialog>

/******************************************************************************/

namespace Ui
{
    class StepExportDialog;
}

class Session;

/*******************************************************************************
*******************************************************************************/
class StepExportDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit StepExportDialog
        (
            Session * const session,
            QWidget * const parent = 0
        );

        ~StepExportDialog
        (
            void
        );

    private:

        void connectSignals
        (
            void
        );

        void saveGeometry
        (
            void
        );

        void restoreGeometry
        (
            void
        );

        void saveState
        (
            void
        );

        void restoreState
        (
            void
        );

        void saveSession
        (
            void
        );

    private slots:

        void browse
        (
            void
        );

        void setSessionType
        (
            int const type
        );

        void finalize
        (
            int result
        );

        virtual void accept
        (
            void
        );

    private:

        Ui::StepExportDialog * ui;

        Session              * session;
};

/******************************************************************************/

#endif /* STEP_EXPORT_DIALOG_H */
