#ifndef CMDPWD_H
#define CMDPWD_H
#include "ftpcommand.h"
#include "bsdsocketfactory.h"
#include <memory>

/**
 * @brief Print working directory
 */
class CmdPwd: public FTPcommand {

    private:
        const int cmdSocket;
        const int dataSocket;
        using FactoryRef = std::unique_ptr<BsdSocketFactory>;
        static inline auto bsdSocketFactory = FactoryRef(new BsdSocketFactoryDefault());

    public:
        /**
         * @brief CmdPwd
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param dataChannelSocket Socket to communication with client on data channel
         */
        CmdPwd(int commandChannelSocket, int dataChannelSocket);
        void execute() override;
        static void setBsdSocketFactory(const BsdSocketFactory &newFactory);

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
};

#endif // CMDPWD_H
