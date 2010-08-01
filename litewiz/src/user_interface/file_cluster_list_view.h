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
class FileClusterListModel;

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

    public:

        void setModel
        (
            FileClusterListModel * model
        );

    protected:

        void createActions
        (
            void
        );

        void connectSignals
        (
            void
        );

        QIntList getSelection
        (
            void
        );

    protected slots:

        void exclude
        (
            void
        );

        void include
        (
            void
        );

        void setSelection
        (
            QItemSelection const & selection
        );

    protected:

        virtual void contextMenuEvent
        (
            QContextMenuEvent * event
        );

        virtual ContextMenuInfo getDefaultContextMenu
        (
            void
        );

        virtual void populateContextMenu
        (
            ContextMenuInfo const &       menuInfo,
            QMenu                 * const menu
        );

    signals:

        void contextMenuRequest
        (
            ContextMenuInfo * const menuInfo
        );

        void excludeRequest
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