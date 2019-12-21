#ifndef FTPSERVICE_H
#define FTPSERVICE_H

#include <QMap>
#include "ftpcommand/ftpcommand.h"
#include "controller/replycodes/replycodes.h"

/**
* @brief Default behaviour of comparing with LT operator on NamedException.
* @return True
*/
bool operator<(const NamedException &, const NamedException &);

/**
* @brief Abstract ftp service class, provide low-level handle of command.
* @abstract Abstract ftp service class, provide low-level handle of command.
*/
class AbstractFTPservice {

    public:
            using ExceptionReplyCode = QMap<NamedException, ReplyCode*>;

    private:
            using CmdRef = std::unique_ptr<AbstractFTPcommand>;

            CmdRef cmd;
            ExceptionReplyCode replyCodes;
            QString errorMsg;

    protected:
            /**
            * @param newCmd Command to handle.
            */
            AbstractFTPservice(AbstractFTPcommand * const newCmd);
            /**
            * @param newCmd Command to handle.
            * @param newReplyCodes Exceptions that may be throw by command and replies assigned to them.
            */
            AbstractFTPservice(AbstractFTPcommand * const newCmd, ExceptionReplyCode newReplyCodes);
            /**
            * @brief Allow to redefined default reply after ending command.
            * @brief Default reply is code number 200.
            * @return Reply before starting command.
            */
            virtual QString parseReplyBefore(AbstractFTPcommand * const);
            /**
            * @brief Allow to redefined default reply after ending command.
            * @brief Default reply is empty string.
            * @return Reply after ending command.
            */
            virtual QString parseReplyAfter(AbstractFTPcommand * const);

    public:
            void start();
            /**
            * @return Reply before starting command.
            */
            QString replyBefore();
            /**
            * @return Reply after ending command.
            */
            QString replyAfter();
            virtual ~AbstractFTPservice() = default;
};

#endif // FTPSERVICE_H
