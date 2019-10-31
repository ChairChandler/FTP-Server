#ifndef REPLYCODES_H
#define REPLYCODES_H

#include <QString>

struct ReplyCodes
{
    QString C200 = "200 Command okay.";
    QString C500 = "500 Syntax error, command unrecognized.";
    QString C501 = "501 Syntax error in parameters or arguments.";
    QString C202 = "202 Command not implemented, superfluous at this site.";
    QString C502 = "502 Command not implemented.";
    QString C503 = "503 Bad sequence of commands.";
    QString C504 = "504 Command not implemented for that parameter.";
    QString C110 = "110 Restart marker reply.";
    QString C11  = "11 System status, or system help reply.";
    QString C212 = "212 Directory status.";
    QString C213 = "213 File status.";
    QString C214 = "214 Help message.";
    QString C215 = "215 NAME system type.";
    QString C120 = "120 Service ready in nnn minutes.";
    QString C220 = "220 Service ready for new user.";
    QString C221 = "221 Service closing control connection.";
    QString C421 = "421 Service not available, closing control connection.";
    QString C125 = "125 Data connection already open; transfer starting.";
    QString C225 = "225 Data connection open; no transfer in progress.";
    QString C425 = "425 Can't open data connection.";
    QString C226 = "226 Closing data connection.";
    QString C426 = "426 Connection closed; transfer aborted.";
    QString C227 = "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).";
    QString C230 = "230 User logged in, proceed.";
    QString C530 = "530 Not logged in.";
    QString C331 = "331 User name okay, need password.";
    QString C332 = "332 Need account for login.";
    QString C532 = "532 Need account for storing files.";
    QString C150 = "150 File status okay; about to open data connection.";
    QString C250 = "250 Requested file action okay, completed.";
    QString C257 = "257 PATHNAME created.";
    QString C350 = "350 Requested file action pending further information.";
    QString C450 = "450 Requested file action not taken.";
    QString C550 = "550 Requested action not taken.";
    QString C451 = "451 Requested action aborted. Local error in processing.";
    QString C551 = "551 Requested action aborted. Page type unknown.";
    QString C452 = "452 Requested action not taken.";
    QString C552 = "552 Requested file action aborted.";
    QString C553 = "553 Requested action not taken.";
};

#endif // REPLYCODES_H
