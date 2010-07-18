/*******************************************************************************
*******************************************************************************/

#ifndef ITEM_LIST_VIEW_H
#define ITEM_LIST_VIEW_H

/******************************************************************************/

#include <QAction>
#include <QListView>

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

    private:

        QAction * excludeAction;
        QAction * includeAction;
};

/******************************************************************************/

#endif /* ITEM_LIST_VIEW_H */
