#ifndef CMDNOOP_H
#define CMDNOOP_H

#include "ftpcommand.h"

/*
 * @brief Empty command that prevents from being disconnected
 */
class CmdNoop: public FTPcommand {

    public:
        CmdNoop() = default;
        void execute() override {}
};

#endif // CMDNOOP_H
