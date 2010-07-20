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

/*******************************************************************************
*******************************************************************************/
class AetExportDialog : public QDialog
{
    Q_OBJECT

    public:

        explicit AetExportDialog
        (
            QWidget *parent = 0
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

    private slots:

        void finalize
        (
            int result
        );

    private:

        Ui::AetExportDialog * ui;
};

/******************************************************************************/

#endif /* AET_EXPORT_DIALOG_H */
