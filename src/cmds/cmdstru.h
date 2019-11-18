#ifndef CMDSTRU_H
#define CMDSTRU_H
#include "ftpcommand.h"
#include "filestructure.h"

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
        FileStructure * const fileStructure;
        int cmdSocket;

    public:
        /**
         * @brief CmdQuit
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param fileStructure Type of files structure
         */
        CmdStru(int commandChannelSocket, FileStructure * const fileStructure);
        void execute() override;

        using AccountNotFoundException = AccountDatabase::AccountNotFoundException;
};

/*TODO: Set File structure as default for files structure.
    File structure is the default to be assumed if the STRUcture
    command has not been used.
*/

/*TODO: Add file structure.
    In file-structure there is no internal structure and the
    file is considered to be a continuous sequence of data
    bytes.
*/


/*TODO: Add record structure.
            Record structures must be accepted for "text" files (i.e.,
            files with TYPE ASCII or EBCDIC) by all FTP implementations.

            In record-structure the file is made up of sequential
            records.
*/

#endif // CMDSTRU_H
