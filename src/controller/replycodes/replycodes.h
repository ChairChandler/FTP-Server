#ifndef REPLYCODES_H
#define REPLYCODES_H

#include <QString>

/**
* @brief Reply code for response.
*/
class ReplyCode {

    private:
        int id;
        QString standardMessage;

    public:
        ReplyCode(int replyID, QString replyMessage);
        QString toString() const;
        int getId() const;
        QString getStandardMessage() const;
};

namespace ReplyCodes {
    static inline ReplyCode C200 = ReplyCode(200, "Command okay.");
    static inline ReplyCode C500 = ReplyCode(500, "Syntax error, command unrecognized.");
    static inline ReplyCode C501 = ReplyCode(501, "Syntax error in parameters or arguments.");
    static inline ReplyCode C202 = ReplyCode(202, "Command not implemented, superfluous at this site.");
    static inline ReplyCode C502 = ReplyCode(502, "Command not implemented.");
    static inline ReplyCode C503 = ReplyCode(503, "Bad sequence of commands.");
    static inline ReplyCode C504 = ReplyCode(504, "Command not implemented for that parameter.");
    static inline ReplyCode C110 = ReplyCode(110, "Restart marker reply.");
    static inline ReplyCode C11  = ReplyCode(11,  "System status, or system help reply.");
    static inline ReplyCode C212 = ReplyCode(212, "Directory status.");
    static inline ReplyCode C213 = ReplyCode(213, "File status.");
    static inline ReplyCode C214 = ReplyCode(214, "Help message.");
    static inline ReplyCode C215 = ReplyCode(215, "NAME system type.");
    static inline ReplyCode C120 = ReplyCode(120, "Service ready in nnn minutes.");
    static inline ReplyCode C220 = ReplyCode(220, "Service ready for new user.");
    static inline ReplyCode C221 = ReplyCode(221, "Service closing control connection.");
    static inline ReplyCode C421 = ReplyCode(421, "Service not available, closing control connection.");
    static inline ReplyCode C125 = ReplyCode(125, "Data connection already open; transfer starting.");
    static inline ReplyCode C225 = ReplyCode(225, "Data connection open; no transfer in progress.");
    static inline ReplyCode C425 = ReplyCode(425, "Can't open data connection.");
    static inline ReplyCode C226 = ReplyCode(226, "Closing data connection.");
    static inline ReplyCode C426 = ReplyCode(426, "Connection closed; transfer aborted.");
    static inline ReplyCode C227 = ReplyCode(227, "Entering Passive Mode (h1,h2,h3,h4,p1,p2).");
    static inline ReplyCode C230 = ReplyCode(230, "User logged in, proceed.");
    static inline ReplyCode C530 = ReplyCode(530, "Not logged in.");
    static inline ReplyCode C331 = ReplyCode(331, "User name okay, need password.");
    static inline ReplyCode C332 = ReplyCode(332, "Need account for login.");
    static inline ReplyCode C532 = ReplyCode(532, "Need account for storing files.");
    static inline ReplyCode C150 = ReplyCode(150, "File status okay; about to open data connection.");
    static inline ReplyCode C250 = ReplyCode(250, "Requested file action okay, completed.");
    static inline ReplyCode C257 = ReplyCode(257, "PATHNAME.");
    static inline ReplyCode C350 = ReplyCode(350, "Requested file action pending further information.");
    static inline ReplyCode C450 = ReplyCode(450, "Requested file action not taken.");
    static inline ReplyCode C550 = ReplyCode(550, "Requested action not taken.");
    static inline ReplyCode C451 = ReplyCode(451, "Requested action aborted. Local error in processing.");
    static inline ReplyCode C551 = ReplyCode(551, "Requested action aborted. Page type unknown.");
    static inline ReplyCode C452 = ReplyCode(452, "Requested action not taken.");
    static inline ReplyCode C552 = ReplyCode(552, "Requested file action aborted.");
    static inline ReplyCode C553 = ReplyCode(553, "Requested action not taken.");
};

#endif // REPLYCODES_H
