#ifndef RETRSERVICE_H
#define RETRSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/retrcmd.h"

/*
               RETR
                  125, 150
                     (110)
                     226, 250
                     425, 426, 451
                  450, 550
                  500, 501, 421, 530
*/

/**
* @brief Service for handling RETR ftp command
*/
class RetrService: public AbstractFTPservice {

    private:
        const QString fileName;
        AbstractFTPservice::ExceptionReplyCode prepareExceptionReplyCode();
        virtual QString parseReplyBefore(AbstractFTPcommand * const) override;
        virtual QString parseReplyAfter(AbstractFTPcommand * const) override;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param fileName Path or name of the file
        */
        RetrService(int commandCommunicationSocket, const QString &fileName);
};

#endif // RETRSERVICE_H
