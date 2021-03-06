/*******************************************************************************
*******************************************************************************/

#include <QFileInfo>
#include <QString>
#include "item.h"
#include "variant.h"
#include "file.h"

/*******************************************************************************
*******************************************************************************/
File::File
(
    QString const & fileName
) :
    info( fileName )
{
    item    = 0;
    variant = 0;
}

/*******************************************************************************
*******************************************************************************/
File::File
(
    QFileInfo const & fileInfo
) :
    info( fileInfo )
{
    item    = 0;
    variant = 0;
}

/*******************************************************************************
*******************************************************************************/
QString File::getPath
(
    void
)
    const
{
    return info.absolutePath();
}

/*******************************************************************************
*******************************************************************************/
QString File::getName
(
    void
)
    const
{
    return info.fileName();
}

/*******************************************************************************
*******************************************************************************/
QString File::getPathName
(
    void
)
    const
{
    return info.absoluteFilePath();
}

/*******************************************************************************
*******************************************************************************/
bool File::isExcluded
(
    void
)
    const
{
    bool result = true;

    if ( ( item != 0 ) && ( variant != 0 ) )
    {
        result = item->isExcluded() || variant->isExcluded();
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
void File::setItem
(
    Item * const item
)
{
    this->item = item;
}

/*******************************************************************************
*******************************************************************************/
Item const * File::getItem
(
    void
)
    const
{
    return item;
}

/*******************************************************************************
*******************************************************************************/
void File::setVariant
(
    Variant * const variant
)
{
    this->variant = variant;
}

/*******************************************************************************
*******************************************************************************/
Variant const * File::getVariant
(
    void
)
    const
{
    return variant;
}

/*******************************************************************************
*******************************************************************************/
bool File::operator==
(
    File const & file
)
    const
{
    return getPathName() == file.getPathName();
}

/******************************************************************************/
