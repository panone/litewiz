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

class Session;
class FileTreeModel;

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

        Ui::MainWindow * ui;

        Session        * session;
        FileTreeModel  * fileTreeModel;
};

/******************************************************************************/

#endif /* MAIN_WINDOW_H */
