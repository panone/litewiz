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

class FileCollection;
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

    private:

        Ui::MainWindow * ui;

        FileCollection * files;
        FileTreeModel  * fileTreeModel;
};

/******************************************************************************/

#endif /* MAIN_WINDOW_H */
