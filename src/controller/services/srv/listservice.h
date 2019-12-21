#ifndef LISTSERVICE_H
#define LISTSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/listcmd.h"

/*
                  LIST
                  125, 150
                     226, 250
                     425, 426, 451
                  450
                  500, 501, 502, 421, 530
*/

/**
* @brief Service for handling LIST ftp command
*/
class ListService: public AbstractFTPservice {

    private:
        AbstractFTPservice::ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Path of the file
        */
        ListService(int commandCommunicationSocket, const QString &path);
};

#endif // LISTSERVICE_H
