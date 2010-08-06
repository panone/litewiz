/*******************************************************************************
*******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

/******************************************************************************/

#include <QList>
#include <QPair>

/******************************************************************************/

typedef QList< int > QIntList;
typedef QPair< int, int > QIntPair;
typedef QList< QIntPair > QIntPairList;

class QString;

/******************************************************************************/

extern int difference
(
    QString const & string1,
    QString const & string2
);

extern QIntList primeFactor
(
    int const number
);

extern QIntPairList pairFactor
(
    int const number
);

extern float cosfade
(
    int const value,
    int const fadeStart,
    int const fadeEnd
);

/******************************************************************************/

#endif /* UTILITY_H */
