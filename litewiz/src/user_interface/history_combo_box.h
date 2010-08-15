/*******************************************************************************
*******************************************************************************/

#ifndef HISTORY_COMBO_BOX_H
#define HISTORY_COMBO_BOX_H

/******************************************************************************/

#include <QComboBox>

/******************************************************************************/

class QStringList;

/*******************************************************************************
*******************************************************************************/
class HistoryComboBox : public QComboBox
{
    Q_OBJECT

    public:

        HistoryComboBox
        (
            QWidget * const parent = 0
        );

    public:

        QStringList getHistory
        (
            void
        );

        void setHistory
        (
            QStringList const & history
        );
};

/******************************************************************************/

#endif /* HISTORY_COMBO_BOX_H */
