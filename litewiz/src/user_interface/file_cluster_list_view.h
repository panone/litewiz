/*******************************************************************************
*******************************************************************************/

#ifndef FILE_CLUSTER_LIST_VIEW_H
#define FILE_CLUSTER_LIST_VIEW_H

/******************************************************************************/

#include <QAction>
#include <QListView>
#include "utility.h"

/******************************************************************************/

class ContextMenuInfo;

/*******************************************************************************
*******************************************************************************/
class FileClusterListView : public QListView
{
    Q_OBJECT

    public:

        FileClusterListView
        (
            QWidget * const parent = 0
        );

    protected:

        QIntList getSelection
        (
            void
        );

        ContextMenuInfo getDefaultContextMenu
        (
            void
        );

    protected slots:

        void excludeItems
        (
            void
        );

        void includeItems
        (
            void
        );

    protected:

        virtual void createActions
        (
            void
        );

        virtual void connectSignals
        (
            void
        );

        virtual void contextMenuEvent
        (
            QContextMenuEvent * event
        );

    signals:

        void contextMenuRequest
        (
            ContextMenuInfo * const menuInfo
        );

        void excludeItemsRequest
        (
            QIntList const &       selection,
            bool             const exclude
        );

    private:

        QAction * excludeAction;
        QAction * includeAction;
};

/******************************************************************************/

#endif /* FILE_CLUSTER_LIST_VIEW_H */
