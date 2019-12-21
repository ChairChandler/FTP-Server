#ifndef CDUPCMD_H
#define CDUPCMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"

/*
         CHANGE TO PARENT DIRECTORY (CDUP)

            This command is a special case of CWD, and is included to
            simplify the implementation of programs for transferring
            directory trees between operating systems having different
            syntaxes for naming the parent directory.  The reply codes
            shall be identical to the reply codes of CWD.
*/

/**
 * @brief Change working directory to parent.
 */
class CdupCmd: public AbstractFTPcommand {

    private:
        const int cmdSocket;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         */
        CdupCmd(int commandChannelSocket);
        void execute() override;
};

#endif // CDUPCMD_H
