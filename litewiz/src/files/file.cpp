/*******************************************************************************
*******************************************************************************/

#include <QFileInfo>
#include <QString>
#include "file.h"

/*******************************************************************************
*******************************************************************************/
File::File
(
    QString const & path
) :
    info( path )
{
}

/*******************************************************************************
*******************************************************************************/
QString File::getPath
(
    void
)
{
    return info.filePath();
}

/*******************************************************************************
*******************************************************************************/
QString File::getName
(
    void
)
{
    return info.fileName();
}

/*******************************************************************************
*******************************************************************************/
QString File::getItem
(
    void
)
{
    return "item";
}

/*******************************************************************************
*******************************************************************************/
QString File::getVariant
(
    void
)
{
    return "variant";
}

/******************************************************************************/
