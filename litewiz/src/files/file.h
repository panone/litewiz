/*******************************************************************************
*******************************************************************************/

#ifndef FILE_H
#define FILE_H

/******************************************************************************/

#include <QFileInfo>
#include <QString>

/*******************************************************************************
*******************************************************************************/
class File
{
    public:

        explicit File
        (
            QString const & fileName
        );

        explicit File
        (
            QFileInfo const & fileInfo
        );

    public:

        QString getPath
        (
            void
        )
        const;

        QString getName
        (
            void
        )
        const;

        QString getItem
        (
            void
        )
        const;

        QString getVariant
        (
            void
        )
        const;

    private:

        QFileInfo info;
};

/******************************************************************************/

#endif /* FILE_H */
