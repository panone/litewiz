/*******************************************************************************
*******************************************************************************/

#include <QtGui/QApplication>
#include <QFont>
#include <QList>
#include <QPalette>
#include <QString>
#include <QStyle>
#include <QVariant>
#include "utility.h"
#include "item.h"
#include "variant.h"
#include "file.h"
#include "file_tree_model.h"
#include "file_tree_item.h"

/*******************************************************************************
*******************************************************************************/
bool FileTreeItem::naturalCompare
(
    FileTreeItem * const item1,
    FileTreeItem * const item2
)
{
    return ::naturalCompare( item1->getName().toUpper(), item2->getName().toUpper() );
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::FileTreeItem
(
    QString const & name
)
{
    directoryName = name;
    expanded      = true;
    file          = 0;
    parent        = 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::FileTreeItem
(
    File const * const file
) :
    file( file )
{
    expanded = false;
    parent   = 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem::~FileTreeItem
(
    void
)
{
    qDeleteAll( children );
}

/*******************************************************************************
*******************************************************************************/
QString FileTreeItem::getPathName
(
    void
)
{
    QString result;

    if ( file != 0 )
    {
        result = file->getPathName();
    }
    else
    {
        result = directoryName;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
bool FileTreeItem::isDirectory
(
    void
)
{
    return file == 0;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::addSubItem
(
    QString const & name
)
{
    FileTreeItem * item = new FileTreeItem( name );

    item->parent = this;

    children.append( item );

    return item;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::addSubItem
(
    File const * const file
)
{
    FileTreeItem * item = new FileTreeItem( file );

    item->parent = this;

    children.append( item );

    return item;
}

/*******************************************************************************
*******************************************************************************/
void FileTreeItem::sort
(
    void
)
{
    foreach ( FileTreeItem * item, children )
    {
        item->sort();
    }

    if ( children.count() > 1 )
    {
        qSort( children.begin(), children.end(), FileTreeItem::naturalCompare );
    }
}

/*******************************************************************************
*******************************************************************************/
void FileTreeItem::expand
(
    bool const expand
)
{
    expanded = expand;
}

/*******************************************************************************
*******************************************************************************/
bool FileTreeItem::isExpanded
(
    void
)
{
    return expanded;
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getRowCount
(
    void
)
    const
{
    return children.count();
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getColumnCount
(
    void
)
    const
{
    return 3;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getData
(
    int const column,
    int const role
)
    const
{
    QVariant result;

    if ( file != 0 )
    {
        switch ( column )
        {
            case 0:
                result = getFileData( role );
                break;

            case 1:
                result = getItemData( role );
                break;

            case 2:
                result = getVariantData( role );
                break;
        }
    }
    else
    {
        if ( column == 0 )
        {
            result = getDirectoryData( role );
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::getParent
(
    void
)
    const
{
    return parent;
}

/*******************************************************************************
*******************************************************************************/
int FileTreeItem::getRow
(
    void
)
    const
{
    int result = 0;

    if ( parent != 0 )
    {
        result = parent->children.indexOf( const_cast< FileTreeItem * >( this ) );
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::findSubItem
(
    QString const & name
)
    const
{
    FileTreeItem * result = 0;

    foreach ( FileTreeItem * item, children )
    {
        if ( item->directoryName == name )
        {
            result = item;
            break;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
FileTreeItem * FileTreeItem::getSubItem
(
    int const row
)
    const
{
    return children.at( row );
}

/*******************************************************************************
*******************************************************************************/
QString FileTreeItem::getName
(
    void
)
{
    QString result;

    if ( file != 0 )
    {
        result = file->getName();
    }
    else
    {
        result = directoryName;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getFileData
(
    int const role
)
    const
{
    QVariant result;

    switch ( role )
    {
        case Qt::DisplayRole:
            result = file->getName();
            break;

        case Qt::ForegroundRole:
            if ( file->isExcluded() )
            {
                result = QApplication::palette().brush( QPalette::Window );
            }
            break;
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getItemData
(
    int const role
)
    const
{
    QVariant result;

    if ( file->getItem() != 0 )
    {
        switch ( role )
        {
            case Qt::DisplayRole:
                result = file->getItem()->getName();
                break;

            case Qt::ForegroundRole:
                if ( file->getItem()->isExcluded() )
                {
                    result = QApplication::palette().brush( QPalette::Window );
                }
                break;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getVariantData
(
    int const role
)
    const
{
    QVariant result;

    if ( file->getVariant() != 0 )
    {
        switch ( role )
        {
            case Qt::DisplayRole:
                result = file->getVariant()->getName();
                break;

            case Qt::ForegroundRole:
                if ( file->getVariant()->isExcluded() )
                {
                    result = QApplication::palette().brush( QPalette::Window );
                }
                break;

            case Qt::FontRole:
                if ( file->getVariant()->isReference() )
                {
                    QFont font;

                    font.setBold( true );

                    result = font;
                }
                break;
        }
    }

    return result;
}

/*******************************************************************************
*******************************************************************************/
QVariant FileTreeItem::getDirectoryData
(
    int const role
)
    const
{
    QVariant result;

    switch ( role )
    {
        case Qt::DisplayRole:
            result = directoryName;
            break;

        case Qt::DecorationRole:
            result = QApplication::style()->standardIcon( QStyle::SP_DirIcon );
            break;

        case FileTreeModel::ExpandedRole:
            result = expanded;
            break;
    }

    return result;
}

/******************************************************************************/
