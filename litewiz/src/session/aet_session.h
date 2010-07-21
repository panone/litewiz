/*******************************************************************************
*******************************************************************************/

#ifndef AET_SESSION_H
#define AET_SESSION_H

/******************************************************************************/

#include <QString>

/******************************************************************************/

class QDomDocument;
class QDomElement;
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

    public:

        void setTitle
        (
            QString const & title
        );

        QString toString
        (
            void
        );

    private:

        QDomElement createDocument
        (
            void
        );

        QDomElement createStringElement
        (
            QString const & name,
            QString const & value
        );

    private:

        Session      * session;
        QDomDocument * document;

        QString        title;
        QString        audioDevice;
};

/******************************************************************************/

#endif /* AET_SESSION_H */
