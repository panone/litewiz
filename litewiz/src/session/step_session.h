/*******************************************************************************
*******************************************************************************/

#ifndef STEP_SESSION_H
#define STEP_SESSION_H

/******************************************************************************/

class QString;
class Session;
class Item;

/*******************************************************************************
*******************************************************************************/
class StepSession
{
    public:

        enum SessionType
        {
            MushraSession = 0,
            AbSession
        };

    public:

        explicit StepSession
        (
            Session * const session
        );

    public:

        void setType
        (
            int const type
        );

        bool save
        (
            QString const & fileName
        );

    private:

        QString formatSession
        (
            QString const & sessionPath
        );

        QString getType
        (
            void
        );

        QString formatItems
        (
            QString const & sessionPath
        );

        QString formatItem
        (
            Item    const * const item,
            QString const &       sessionPath
        );

    private:

        Session * session;

        int       type;
};

/******************************************************************************/

#endif /* STEP_SESSION_H */
