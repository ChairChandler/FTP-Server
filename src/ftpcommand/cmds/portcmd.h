#ifndef PORTCMD_H
#define PORTCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"
#include "bsdsocket/bsdsocketfactory.h"

/*
         DATA PORT (PORT)

            The argument is a HOST-PORT specification for the data port
            to be used in data connection.  There are defaults for both
            the user and server data ports, and under normal
            circumstances this command and its reply are not needed.  If
            this command is used, the argument is the concatenation of a
            32-bit internet host address and a 16-bit TCP port address.
            This address information is broken into 8-bit fields and the
            value of each field is transmitted as a decimal number (in
            character string representation).  The fields are separated
            by commas.  A port command would be:

               PORT h1,h2,h3,h4,p1,p2

            where h1 is the high order 8 bits of the internet host
            address.
*/

/**
* @brief Creates a new data communication channel.
*/
class PortCmd : public AbstractFTPcommand {

    private:
        const sockaddr_in address;
        const int cmdSocket;

    public:
        /**
         * @param commandChannelSocket Client command channel socket
         * @param address Client data communication channel address
         */
        PortCmd(int commandChannelSocket, sockaddr_in address);
        void execute() override;
};

#endif // PORTCMD_H
