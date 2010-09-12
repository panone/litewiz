/*******************************************************************************
*******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

/******************************************************************************/

#include <QList>
#include <QPair>
#include <QSet>

/******************************************************************************/

typedef QList< int > QIntList;
typedef QListIterator< int > QIntListIterator;
typedef QSet< int > QIntSet;
typedef QSetIterator< int > QIntSetIterator;
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

extern int gcd
(
    int const number1,
    int const number2
);

extern int gcd
(
    QIntList const & numbers
);

extern int gcd
(
    QIntSet const & numbers
);

/******************************************************************************/

#endif /* UTILITY_H */
