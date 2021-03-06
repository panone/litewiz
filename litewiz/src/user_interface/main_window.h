/*******************************************************************************
*******************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/******************************************************************************/

#include <QMainWindow>

/******************************************************************************/

namespace Ui
{
    class MainWindow;
}

class FileTreeModel;
class ItemListModel;
class VariantListModel;
class Session;

/*******************************************************************************
*******************************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow
        (
            QWidget * parent = 0
        );

        ~MainWindow
        (
            void
        );

    private:

        void setupUi
        (
            void
        );

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

        void enableExport
        (
            void
        );

        void enableClassify
        (
            void
        );

        void addFiles
        (
            void
        );

        void addDirectory
        (
            void
        );

        void exportAetSession
        (
            void
        );

        void exportStepSession
        (
            void
        );

        void showOptionsDialog
        (
            void
        );

        void updateFileTreeView
        (
            void
        );

        void updateVariance
        (
            void
        );

    signals:

        void settingsChanged
        (
            void
        );

    private:

        virtual void closeEvent
        (
            QCloseEvent * event
        );

    private:

        Ui::MainWindow   * ui;

        Session          * session;

        FileTreeModel    * fileTreeModel;
        ItemListModel    * itemListModel;
        VariantListModel * variantListModel;
};

/******************************************************************************/

#endif /* MAIN_WINDOW_H */
