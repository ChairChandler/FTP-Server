#ifndef CMDPORT_H
#define CMDPORT_H
#include "src/ftpcommand.h"
#include <arpa/inet.h>
#include <netinet/ip.h>

/**
 * @brief Creates a new data communication stream
 */
class CmdPort : public FTPcommand {

    private:
        const sockaddr_in address;
        const int cmdSocket;
        int dataSocket = -1;

    public:
        /**
         * @brief CmdPort
         * @param commandStreamSocket Client command stream socket
         * @param address Client data communication server address
         */
        CmdPort(int commandStreamSocket, sockaddr_in address);
        bool execute() override;
        int getDataStreamSocket();

        struct DataStreamSocketNotExistsException: std::exception {};
};

#endif // CMDPORT_H
