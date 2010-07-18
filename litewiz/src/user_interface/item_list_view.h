/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_LIST_VIEW_H
#define ITEM_LIST_VIEW_H

/******************************************************************************/

#include <QAction>
#include <QListView>
#include "utility.h"

/*******************************************************************************
*******************************************************************************/
class ItemListView : public QListView
{
    Q_OBJECT

    public:

        ItemListView
        (
            QWidget * const parent = 0
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

        QIntList getSelection
        (
            void
        );

    private slots:

        void excludeItems
        (
            void
        );

        void includeItems
        (
            void
        );

    private:

        virtual void contextMenuEvent
        (
            QContextMenuEvent * event
        );

    signals:

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

#endif /* ITEM_LIST_VIEW_H */
