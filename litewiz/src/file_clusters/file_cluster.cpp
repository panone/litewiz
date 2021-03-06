/*******************************************************************************
*******************************************************************************/

#include <QList>
#include <QString>
#include "file_cluster.h"

/*******************************************************************************
*******************************************************************************/
FileCluster::FileCluster
(
    QString                const & name,
    QString                const & stem,
    QList< FileCluster * > const & collection
) :
    name( name ),
    stem( stem ),
    collection( collection )
{
    excluded = false;
}

/*******************************************************************************
*******************************************************************************/
QString FileCluster::getName
(
    void
)
    const
{
    return name;
}

/*******************************************************************************
*******************************************************************************/
void FileCluster::setName
(
    QString const & name
)
{
    this->name = name;
}

/*******************************************************************************
*******************************************************************************/
QString FileCluster::getStem
(
    void
)
    const
{
    return stem;
}

/*******************************************************************************
*******************************************************************************/
int FileCluster::getIndex
(
    void
)
    const
{
    return collection.indexOf( const_cast< FileCluster * >( this ) );
}

/*******************************************************************************
*******************************************************************************/
void FileCluster::exclude
(
    bool const exclude
)
{
    excluded = exclude;
}

/*******************************************************************************
*******************************************************************************/
bool FileCluster::isExcluded
(
    void
)
    const
{
    return excluded;
}

/******************************************************************************/
