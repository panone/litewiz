/*******************************************************************************
*******************************************************************************/

#ifndef UTILITY_H
#define UTILITY_H

/******************************************************************************/

#include <QList>

/******************************************************************************/

typedef QList< int > QIntList;

/*******************************************************************************
*******************************************************************************/
class ConstRunnable
{
    public:

        virtual void run
        (
            void
        )
        const
        = 0;
};

/*******************************************************************************
*******************************************************************************/
#define DEFINE_CONST_RUNNABLE_2( name, type1, name1, type2, name2 ) \
class name : public ConstRunnable { \
public: name( type1 name1, type2 name2 ) : name1( name1 ), name2( name2 ){} \
public: virtual void run( void ) const; \
protected: type1 name1; type2 name2; }; \
void name::run( void ) const

/*******************************************************************************
*******************************************************************************/
template< typename Type >
Type qMin
(
    QList< Type > const & list
)
{
    Type result = list.first();

    foreach ( Type value, list )
    {
        result = qMin( result, value );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
template< typename Type >
Type qMax
(
    QList< Type > const & list
)
{
    Type result = list.first();

    foreach ( Type value, list )
    {
        result = qMax( result, value );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/

extern bool naturalCompare
(
    QString const & string1,
    QString const & string2
);

/******************************************************************************/

#endif /* UTILITY_H */
