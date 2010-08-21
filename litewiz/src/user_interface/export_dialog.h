/*******************************************************************************
*******************************************************************************/

#ifndef EXPORT_DIALOG_H
#define EXPORT_DIALOG_H

/******************************************************************************/

#include <QDialog>
#include <QString>

/******************************************************************************/

class QPushButton;
class QSettings;
class QWidget;
class HistoryComboBox;
class Session;

/*******************************************************************************
*******************************************************************************/
class ExportDialog : public QDialog
{
    Q_OBJECT

    public:

        class BrowseInfo
        {
            public:

                BrowseInfo
                (
                    QString const & caption,
                    QString const & pattern
                );

            public:

                QString   caption;
                QString   pattern;
        };

    public:

        explicit ExportDialog
        (
            Session * const session,
            QWidget * const parent = 0
        );

    protected:

        void initializeFilePicker
        (
            HistoryComboBox * const fileNameEdit,
            QPushButton     * const browseButton
        );

        void saveState
        (
            void
        );

        void restoreState
        (
            void
        );

        bool confirmOverwrite
        (
            QString const & fileName
        );

    protected slots:

        void initialize
        (
            void
        );

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

    protected:

        virtual QString getSettingsName
        (
            void
        )
        = 0;

        virtual BrowseInfo getBrowseInfo
        (
            void
        )
        = 0;

        virtual void connectSignals
        (
            void
        );

        virtual void saveGeometry
        (
            void
        );

        virtual void restoreGeometry
        (
            void
        );

        virtual void saveState
        (
            QSettings * const settings
        )
        = 0;

        virtual void restoreState
        (
            QSettings const & settings
        )
        = 0;

        virtual void saveSession
        (
            void
        )
        = 0;

    protected:

        Session         * session;

        HistoryComboBox * fileNameEdit;
        bool              overwriteConfirmed;
        QString           confirmedFileName;
};

/******************************************************************************/

#endif /* EXPORT_DIALOG_H */
