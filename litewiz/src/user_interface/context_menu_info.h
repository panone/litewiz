/*******************************************************************************
*******************************************************************************/

#ifndef CONTEXT_MENU_INFO_H
#define CONTEXT_MENU_INFO_H

/******************************************************************************/

#include <QSet>
#include "utility.h"

/*******************************************************************************
*******************************************************************************/
class ContextMenuInfo
{
    public:

        enum
        {
            Exclude,
            Include,
            ReferenceChecked,
            ReferenceUnchecked
        };

    public:

        ContextMenuInfo
        (
            QIntList const & selection
        );

    public:

        QIntList getSelection
        (
            void
        )
        const;

        void addMenuEntry
        (
            int const entry
        );

        bool hasMenuEntry
        (
            int const entry
        )
        const;

        void clearMenuEntries
        (
            void
        );

    private:

    	QIntList      selection;
    	QSet< int >   entries;
};

/******************************************************************************/

#endif /* CONTEXT_MENU_INFO_H */
