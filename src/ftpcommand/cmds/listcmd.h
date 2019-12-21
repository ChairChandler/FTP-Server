#ifndef LISTCMD_H
#define LISTCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"
#include "bsdsocket/bsdsocketfactory.h"

/*
            LIST (LIST)

            This command causes a list to be sent from the server to the
            passive DTP.  If the pathname specifies a directory or other
            group of files, the server should transfer a list of files
            in the specified directory.  If the pathname specifies a
            file then the server should send current information on the
            file.  A null argument implies the user's current working or
            default directory.  The data transfer is over the data
            connection in type ASCII or type EBCDIC.  (The user must
            ensure that the TYPE is appropriately ASCII or EBCDIC).
            Since the information on a file may vary widely from system
            to system, this information may be hard to use automatically
            in a program, but may be quite useful to a human user.
*/

/**
 * @brief Send information to the data communication channel about files in directory, or specified file.
 * Directory can be specified or not - then it implies the user's current working directory.
 */
class ListCmd : public AbstractFTPcommand {

    private:
        int cmdSocket;
        QString path;

        using FactoryRef = std::unique_ptr<InterfaceBsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault);

        void send(const QStringList &filesInfo, const sockaddr_in &addr);

    public:
        /**
         * @param commandCommunicationSocket Socket to communication with client on command channel
         * @param path Path to the directory
         */
        ListCmd(int commandCommunicationSocket, const QString &path);
        virtual void execute() override;
        void setBsdSocketFactory(const InterfaceBsdSocketFactory &newBsdSocketFactory);
};

#endif // LISTCMD_H
