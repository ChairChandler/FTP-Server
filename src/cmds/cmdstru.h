#ifndef CMDSTRU_H
#define CMDSTRU_H
#include "ftpcommand.h"
#include "structure/structure.h"

/*
         FILE STRUCTURE (STRU)

            The argument is a single Telnet character code specifying
            file structure described in the Section on Data
            Representation and Storage.

            The following codes are assigned for structure:

               F - File (no record structure)
               R - Record structure

            The default structure is File.
*/

/*
 * @brief Change type of files structure
 */
class CmdStru: public FTPcommand  {

    private:
        Structure * const structure;
        int cmdSocket;

    public:
        /**
         * @brief CmdQuit
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param fileStructure Type of files structure
         */
        CmdStru(int commandChannelSocket, Structure * const structure);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
};

/*TODO: Add file structure.
    In file-structure there is no internal structure and the
    file is considered to be a continuous sequence of data
    bytes.
*/

#endif // CMDSTRU_H
