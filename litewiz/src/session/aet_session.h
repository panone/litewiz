/*******************************************************************************
*******************************************************************************/

#ifndef AET_SESSION_H
#define AET_SESSION_H

/******************************************************************************/

#include <QString>

/******************************************************************************/

class QDomDocument;
class QDomElement;
class QStringList;
class Session;

/*******************************************************************************
*******************************************************************************/
class AetSession
{
    public:

        explicit AetSession
        (
            Session * const session
        );

        ~AetSession
        (
            void
        );

    public:

        void setTitle
        (
            QString const & title
        );

        void setAudioDevice
        (
            QString const & deviceName
        );

        QString toString
        (
            void
        );

    private:

        void formatSession
        (
            QDomElement parent
        );

        void formatVariants
        (
            QDomElement parent
        );

        QDomElement createStringElement
        (
            QString const & name,
            QString const & value
        );

        QDomElement createStringListElement
        (
            QString     const & name,
            QStringList const & values
        );

    private:

        Session      * session;
        QDomDocument * document;

        QString        title;
        QString        audioDevice;
};

/******************************************************************************/

#endif /* AET_SESSION_H */
