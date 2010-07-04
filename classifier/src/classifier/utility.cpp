/*******************************************************************************
*******************************************************************************/

#include <QString>
#include <algorithm>
#include "utility.h"

using namespace std;

/*******************************************************************************
*******************************************************************************/
int difference
(
    QString const & string1,
    QString const & string2
)
{
    int           result = 0;
    QChar const * data1  = string1.constData();
    QChar const * data2  = string2.constData();
    int           length = min( string1.length(), string2.length() );

    while ( ( result < length ) && ( *data1++ == *data2++ ) )
    {
        ++result;
    }

    return result;
}

/******************************************************************************/
