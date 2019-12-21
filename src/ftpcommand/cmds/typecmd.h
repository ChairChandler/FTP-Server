#ifndef TYPECMD_H
#define TYPECMD_H
#pragma GCC diagnostic ignored "-Wpadded"

#include "ftpcommand/ftpcommand.h"
#include "transmission/filetransmission.h"

/*
         REPRESENTATION TYPE (TYPE)

            The argument specifies the representation type as described
            in the Section on Data Representation and Storage.  Several
            types take a second parameter.  The first parameter is
            denoted by a single Telnet character, as is the second
            Format parameter for ASCII and EBCDIC; the second parameter
            for local byte is a decimal integer to indicate Bytesize.
            The parameters are separated by a <SP> (Space, ASCII code
            32).

            The following codes are assigned for type:

                         \    /
               A - ASCII |    | N - Non-print
                         |-><-| T - Telnet format effectors
               E - EBCDIC|    | C - Carriage Control (ASA)
                         /    \
               I - Image

               L <byte size> - Local byte Byte size

            The default representation type is ASCII Non-print.  If the
            Format parameter is changed, and later just the first
            argument is changed, Format then returns to the Non-print
            default.
*/

/**
 * @brief Change type of transmission
 */
class TypeCmd: public AbstractFTPcommand {

    private:
        AccountInfo::TransmissionType transmission;
        int cmdSocket;

    public:
        /**
         * @param commandChannelSocket Socket to communication with client on command channel
         * @param newTransmissionType Type of transmission
         */
        TypeCmd(int commandChannelSocket, AccountInfo::TransmissionType newTransmissionType);
        void execute() override;
};

#endif // TYPECMD_H
