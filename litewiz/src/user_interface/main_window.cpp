/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include "main_window.h"
#include "file_collection.h"
#include "file_tree_model.h"
#include "ui_main_window.h"

/*******************************************************************************
*******************************************************************************/
MainWindow::MainWindow
(
    QWidget * parent
) :
    QMainWindow( parent )
{
    ui = new Ui::MainWindow();

    ui->setupUi( this );

    files = new FileCollection();

    files->load( QApplication::instance()->arguments().at( 1 ) );

    fileTreeModel = new FileTreeModel( files, this );

    ui->filesTreeView->setModel( fileTreeModel );
    //ui->filesTreeView->setRootIsDecorated( false );
}

/*******************************************************************************
*******************************************************************************/
MainWindow::~MainWindow
(
    void
)
{
    delete files;
    delete ui;
}

/******************************************************************************/
