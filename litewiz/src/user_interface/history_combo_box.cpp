/*******************************************************************************
*******************************************************************************/

#include <QComboBox>
#include <QLineEdit>
#include <QStringList>
#include "history_combo_box.h"

/******************************************************************************/

static int const maxHistoryLength = 15;

/*******************************************************************************
*******************************************************************************/
HistoryComboBox::HistoryComboBox
(
    QWidget * const parent
) :
    QComboBox( parent )
{
}

/*******************************************************************************
*******************************************************************************/
QStringList HistoryComboBox::getHistory
(
    void
)
{
    QStringList result;

    if ( ( lineEdit() != 0 ) && !lineEdit()->text().isEmpty() )
    {
        result.append( lineEdit()->text() );
    }

    int historyLength = qMin( count(), maxHistoryLength );

    for ( int i = 0; i < historyLength; i++ )
    {
        result.append( itemText( i ) );
    }

    result.removeDuplicates();

    return result;
}

/*******************************************************************************
*******************************************************************************/
void HistoryComboBox::setHistory
(
    QStringList const & history
)
{
    insertItems( 0, history );
}

/******************************************************************************/
