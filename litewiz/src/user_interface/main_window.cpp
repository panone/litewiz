/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include "main_window.h"
#include "session.h"
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

    session = new Session( this );

    session->loadFileList( QApplication::instance()->arguments().at( 1 ) );

    fileTreeModel = new FileTreeModel( session, this );

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
    delete ui;
}

/******************************************************************************/
