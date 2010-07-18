/*******************************************************************************
*******************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

/******************************************************************************/

#include <QMainWindow>

/******************************************************************************/

namespace Ui {
    class MainWindow;
}

class FileTreeModel;
class ItemListModel;
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

        void saveGeometry
        (
            void
        );

        void restoreGeometry
        (
            void
        );

    private slots:

        void addFiles
        (
            void
        );

        void addDirectory
        (
            void
        );

    private:

        virtual void closeEvent
        (
            QCloseEvent * event
        );

    private:

        Ui::MainWindow * ui;

        Session        * session;
        FileTreeModel  * fileTreeModel;
        ItemListModel  * itemListModel;
};

/******************************************************************************/

#endif /* MAIN_WINDOW_H */
