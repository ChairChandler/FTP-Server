#ifndef STORSERVICE_H
#define STORSERVICE_H

#include "controller/services/FTPservice.h"
#include "ftpcommand/cmds/storcmd.h"

/*
               STOR
                  125, 150
                     (110)
                     226, 250
                     425, 426, 451, 551, 552
                  532, 450, 452, 553
                  500, 501, 421, 530
*/

/**
* @brief Service for handling STOR ftp command
*/
class StorService: public AbstractFTPservice {

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
        StorService(int commandCommunicationSocket, const QString &fileName);
};

#endif // STORSERVICE_H
