#ifndef CWDCMD_H
#define CWDCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"

/*
         CHANGE WORKING DIRECTORY (CWD)

            This command allows the user to work with a different
            directory or dataset for file storage or retrieval without
            altering his login or accounting information.  Transfer
            parameters are similarly unchanged.  The argument is a
            pathname specifying a directory or other system dependent
            file group designator.
*/

/**
 * @brief Change working directory.
 */
class CwdCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        const QString path;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path New path
         */
        CwdCmd(int commandChannelSocket, const QString &path);
        void execute() override;
};

#endif // CWDCMD_H
