#ifndef RMDCMD_H
#define RMDCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"

/*
         REMOVE DIRECTORY (RMD)

            This command causes the directory specified in the pathname
            to be removed as a directory (if the pathname is absolute)
            or as a subdirectory of the current working directory (if
            the pathname is relative).
*/

/**
 * @brief Remove directory in specified directory.
 */
class RmdCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        const QString path;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Absolute path to the dir or relative to the current working directory
         */
        RmdCmd(int commandChannelSocket, const QString &path);
        void execute() override;
};

#endif // RMDCMD_H
