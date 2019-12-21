#ifndef RETRCMD_H
#define RETRCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include <memory>
#include "ftpcommand/ftpcommand.h"
#include "bsdsocket/bsdsocketfactory.h"
#include "transmission/filetransmission.h"

/*
         RETRIEVE (RETR)

            This command causes the server-DTP to transfer a copy of the
            file, specified in the pathname, to the server- or user-DTP
            at the other end of the data connection.  The status and
            contents of the file at the server site shall be unaffected.

*/

/**
 * @brief Upload file to the client.
 */
class RetrCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        const QString fileName;

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault);

        void send(const sockaddr_in &addr, const QString &sourcePath, AbstractFileTransmission * const trans);

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Absolute path to the dir or relative to the current working directory
         */
        RetrCmd(int commandChannelSocket, const QString &fileName);
        void execute() override;
        void setBsdSocketFactory(const InterfaceBsdSocketFactory &newBsdSocketFactory);
};
#endif // RETRCMD_H
