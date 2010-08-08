/*******************************************************************************
*******************************************************************************/

#ifndef FILE_TREE_VIEW_H
#define FILE_TREE_VIEW_H

/******************************************************************************/

#include <QTreeView>

/******************************************************************************/

class FileTreeModel;

/*******************************************************************************
*******************************************************************************/
class FileTreeView : public QTreeView
{
    Q_OBJECT

    public:

        FileTreeView
        (
            QWidget * const parent = 0
        );

    public:

        void setModel
        (
            FileTreeModel * model
        );

    private:

        void createActions
        (
            void
        );

        void connectSignals
        (
            void
        );

    private slots:

        void remove
        (
            void
        );

    public:

        virtual void reset
        (
            void
        );

    private:

        virtual void keyPressEvent
        (
            QKeyEvent * event
        );

        virtual void contextMenuEvent
        (
            QContextMenuEvent * event
        );

    signals:

        void removeRequest
        (
            QModelIndexList const & selection
        );

    private:

        QAction * removeAction;
};

/******************************************************************************/

#endif /* FILE_TREE_VIEW_H */
