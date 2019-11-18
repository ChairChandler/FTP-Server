#ifndef CMDMODE_H
#define CMDMODE_H
#include "ftpcommand.h"
#include "mode.h"

/*
         TRANSFER MODE (MODE)

            The argument is a single Telnet character code specifying
            the data transfer modes described in the Section on
            Transmission Modes.

            The following codes are assigned for transfer modes:

               S - Stream

            The default transfer mode is Stream.
*/

/*
 * @brief Change mode of transmission
 */
class CmdMode: public FTPcommand {

    private:
        Mode * const mode;
        int cmdSocket;

    public:
       /**
        * @brief CmdPort
        * @param commandChannelSocket Client command channel socket
        * @param mode Type of mode
        */
        CmdMode(int commandChannelSocket, Mode * const mode);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
};

#endif // CMDMODE_H
