#ifndef STORCMD_H
#define STORCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include <memory>
#include "ftpcommand/ftpcommand.h"
#include "bsdsocket/bsdsocketfactory.h"
#include "transmission/filetransmission.h"


/*
         STORE (STOR)

            This command causes the server-DTP to accept the data
            transferred via the data connection and to store the data as
            a file at the server site.  If the file specified in the
            pathname exists at the server site, then its contents shall
            be replaced by the data being transferred.  A new file is
            created at the server site if the file specified in the
            pathname does not already exist.
*/

/**
 * @brief Download file from the client.
 */
class StorCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        const QString fileName;

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault);

        void receive(const sockaddr_in &addr, const QString &destinationPath, AbstractFileTransmission * const trans);

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Absolute path to the dir or relative to the current working directory
         */
        StorCmd(int commandChannelSocket, const QString &fileName);
        void execute() override;
        void setBsdSocketFactory(const InterfaceBsdSocketFactory &newBsdSocketFactory);
};

#endif // STORCMD_H
