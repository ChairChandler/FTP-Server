#ifndef CMDPORT_H
#define CMDPORT_H
#include "ftpcommand.h"
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
        void execute() override;
        int getDataStreamSocket() const;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
        struct CannotConnectException: std::exception {};
        struct DataStreamSocketNotExistsException: std::exception {};
};

#endif // CMDPORT_H
