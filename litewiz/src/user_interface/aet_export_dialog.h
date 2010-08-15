/*******************************************************************************
*******************************************************************************/

#ifndef AET_EXPORT_DIALOG_H
#define AET_EXPORT_DIALOG_H

/******************************************************************************/

#include <QDialog>

/******************************************************************************/

namespace Ui
{
    class AetExportDialog;
}

class Session;

/*******************************************************************************
*******************************************************************************/
class AetExportDialog : public QDialog
{
    Q_OBJECT

    public:

        explicit AetExportDialog
        (
            Session * const session,
            QWidget * const parent = 0
        );

        ~AetExportDialog
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

        void finalize
        (
            int result
        );

        virtual void accept
        (
            void
        );

    private:

        Ui::AetExportDialog * ui;

        Session             * session;
};

/******************************************************************************/

#endif /* AET_EXPORT_DIALOG_H */
