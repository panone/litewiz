/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QFileDialog>
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

    connect( ui->addDirectoryAction, SIGNAL( triggered() ), this, SLOT( addDirectory() ) );

    session = new Session( this );

    if ( QApplication::instance()->arguments().count() > 1 )
    {
        session->loadFileList( QApplication::instance()->arguments().at( 1 ) );
    }

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

/*******************************************************************************
*******************************************************************************/
void MainWindow::addDirectory
(
    void
)
{
    QString directoryName =  QFileDialog::getExistingDirectory( this );

    if ( !directoryName.isNull() )
    {
        session->addDirectory( directoryName );
    }
}

/******************************************************************************/
