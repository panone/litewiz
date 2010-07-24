/*******************************************************************************
*******************************************************************************/

#include <QString>
#include "variant.h"

/*******************************************************************************
*******************************************************************************/
Variant::Variant
(
    QString const & name,
    QString const & stem
) :
    name( name ),
    stem( stem )
{
    reference = false;
    excluded  = false;
}

/*******************************************************************************
*******************************************************************************/
QString Variant::getName
(
    void
)
    const
{
    return name;
}

/*******************************************************************************
*******************************************************************************/
QString Variant::getStem
(
    void
)
    const
{
    return stem;
}

/*******************************************************************************
*******************************************************************************/
void Variant::setReference
(
    bool const reference
)
{
    this->reference = reference;
}

/*******************************************************************************
*******************************************************************************/
bool Variant::isReference
(
    void
)
    const
{
    return reference;
}

/*******************************************************************************
*******************************************************************************/
void Variant::exclude
(
    bool const exclude
)
{
    excluded = exclude;
}

/*******************************************************************************
*******************************************************************************/
bool Variant::isExcluded
(
    void
)
    const
{
    return excluded;
}

/******************************************************************************/