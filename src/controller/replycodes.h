#ifndef REPLYCODES_H
#define REPLYCODES_H
#include <QString>
#include <QList>
#include <QMap>

class ReplyCode {
        int id;
        QString standardMessage;
        QMap<QString, int> keywords;

    public:
        ReplyCode(int replyID, QString replyMessage);
        ReplyCode(int replyID, QString replyMessage, QList<QString> args);
        QString toString() const;
        QString toString(QMap<QString, QString> replacementArgs) const;
        int getId() const;
        QString getStandardMessage() const;
};

struct ReplyCodes {
    ReplyCode C200 = ReplyCode(200, "Command okay.");
    ReplyCode C500 = ReplyCode(500, "Syntax error, command unrecognized.");
    ReplyCode C501 = ReplyCode(501, "Syntax error in parameters or arguments.");
    ReplyCode C202 = ReplyCode(202, "Command not implemented, superfluous at this site.");
    ReplyCode C502 = ReplyCode(502, "Command not implemented.");
    ReplyCode C503 = ReplyCode(503, "Bad sequence of commands.");
    ReplyCode C504 = ReplyCode(504, "Command not implemented for that parameter.");
    ReplyCode C110 = ReplyCode(110, "Restart marker reply.");
    ReplyCode C11  = ReplyCode(11,  "System status, or system help reply.");
    ReplyCode C212 = ReplyCode(212, "Directory status.");
    ReplyCode C213 = ReplyCode(213, "File status.");
    ReplyCode C214 = ReplyCode(214, "Help message.");
    ReplyCode C215 = ReplyCode(215, "NAME system type.", {"NAME"});
    ReplyCode C120 = ReplyCode(120, "Service ready in nnn minutes.", {"nnn"});
    ReplyCode C220 = ReplyCode(220, "Service ready for new user.");
    ReplyCode C221 = ReplyCode(221, "Service closing control connection.");
    ReplyCode C421 = ReplyCode(421, "Service not available, closing control connection.");
    ReplyCode C125 = ReplyCode(125, "Data connection already open; transfer starting.");
    ReplyCode C225 = ReplyCode(225, "Data connection open; no transfer in progress.");
    ReplyCode C425 = ReplyCode(425, "Can't open data connection.");
    ReplyCode C226 = ReplyCode(226, "Closing data connection.");
    ReplyCode C426 = ReplyCode(426, "Connection closed; transfer aborted.");
    ReplyCode C227 = ReplyCode(227, "Entering Passive Mode (h1,h2,h3,h4,p1,p2).", {"(h1,h2,h3,h4,p1,p2)"});
    ReplyCode C230 = ReplyCode(230, "User logged in, proceed.");
    ReplyCode C530 = ReplyCode(530, "Not logged in.");
    ReplyCode C331 = ReplyCode(331, "User name okay, need password.");
    ReplyCode C332 = ReplyCode(332, "Need account for login.");
    ReplyCode C532 = ReplyCode(532, "Need account for storing files.");
    ReplyCode C150 = ReplyCode(150, "File status okay; about to open data connection.");
    ReplyCode C250 = ReplyCode(250, "Requested file action okay, completed.");
    ReplyCode C257 = ReplyCode(257, "PATHNAME created.", {"PATHNAME"});
    ReplyCode C350 = ReplyCode(350, "Requested file action pending further information.");
    ReplyCode C450 = ReplyCode(450, "Requested file action not taken.");
    ReplyCode C550 = ReplyCode(550, "Requested action not taken.");
    ReplyCode C451 = ReplyCode(451, "Requested action aborted. Local error in processing.");
    ReplyCode C551 = ReplyCode(551, "Requested action aborted. Page type unknown.");
    ReplyCode C452 = ReplyCode(452, "Requested action not taken.");
    ReplyCode C552 = ReplyCode(552, "Requested file action aborted.");
    ReplyCode C553 = ReplyCode(553, "Requested action not taken.");
/*    QString C200 = "200 Command okay.";
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
    QString C553 = "553 Requested action not taken.";*/
};

#endif // REPLYCODES_H
