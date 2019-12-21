#ifndef MKDCMD_H
#define MKDCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"

/*
         MAKE DIRECTORY (MKD)

            This command causes the directory specified in the pathname
            to be created as a directory (if the pathname is absolute)
            or as a subdirectory of the current working directory (if
            the pathname is relative).
*/

/**
 * @brief Create directory in specified directory.
 */
class MkdCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;
        const QString path;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param path Absolute path to the new dir or relative to the current working directory
         */
        MkdCmd(int commandChannelSocket, const QString &path);
        void execute() override;
};

#endif // MKDCMD_H
