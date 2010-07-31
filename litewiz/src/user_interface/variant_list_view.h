/*******************************************************************************
*******************************************************************************/

#ifndef VARIANT_LIST_VIEW_H
#define VARIANT_LIST_VIEW_H

/******************************************************************************/

#include "file_cluster_list_view.h"

/******************************************************************************/

class QAction;
class VariantListModel;

/*******************************************************************************
*******************************************************************************/
class VariantListView : public FileClusterListView
{
    Q_OBJECT

    public:

        VariantListView
        (
            QWidget * const parent = 0
        );

    public:

        void setModel
        (
            VariantListModel * model
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

        void setReference
        (
            void
        );

    private:

        virtual void populateContextMenu
        (
            ContextMenuInfo const &       menuInfo,
            QMenu                 * const menu
        );

    signals:

        void referenceChanged
        (
            QModelIndex const & index
        );

    private:

        QAction * setReferenceAction;
};

/******************************************************************************/

#endif /* VARIANT_LIST_VIEW_H */
