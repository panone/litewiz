/*******************************************************************************
*******************************************************************************/

#ifndef OPTIONS_DIALOG_H
#define OPTIONS_DIALOG_H

/******************************************************************************/

#include <QDialog>

/******************************************************************************/

namespace Ui
{
    class OptionsDialog;
}

/*******************************************************************************
*******************************************************************************/
class OptionsDialog : public QDialog
{
    Q_OBJECT

    public:

        explicit OptionsDialog
        (
            QWidget * const parent = 0
        );

        virtual ~OptionsDialog
        (
            void
        );

    private:

        void saveState
        (
            void
        );

        void restoreState
        (
            void
        );

    private slots:

        virtual void accept
        (
            void
        );

    private:

        Ui::OptionsDialog *ui;
};

/******************************************************************************/

#endif /* OPTIONS_DIALOG_H */
