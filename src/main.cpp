#include <QTextStream>
#include <QApplication>
#include <QDesktopServices>
#include <QtConcurrent/QtConcurrent>
#include "controller/ftpcontroller.h"
#include "controller/ftpconnectionworker.h"
#include "controller/xmloutput/xmlcout.h"
#include "controller/xmloutput/xmlexception.h"
#include "controller/xmloutput/xmllogs.h"


static const QString outputChar = "o", outputStr = "output";
static const QString logsChar = "l", logsStr = "logs";
static const QString timeoutChar = "t", timeoutStr = "timeout";
static const QString rootChar = "r", rootStr = "root";
static const QString authorChar = "a", authorStr = "author";
static const QString standardChar = "s", standardStr = "standard";


void initApp(QCoreApplication &a);
QPair<QString, int> parseArgv(QCoreApplication &a);
void initParser(QCommandLineParser &parser, QCoreApplication &a);


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    initApp(a);

    auto pair = parseArgv(a);
    QString ip = pair.first;
    int port = pair.second;

    //run server in another thread
    QtConcurrent::run([&ip, &port, &a](){
        try {
            FTPcontroller server(ip, port);
            server.start();
        } catch (XmlException &e) {
            QTextStream(stderr) << e.what() << endl;
            a.exit(EXIT_FAILURE);
        }
    });

    return a.exec();
}

void initApp(QCoreApplication &a) {
    a.setApplicationName("Simple FTP server");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Adam Lewandowski");
    a.setOrganizationDomain("https://github.com/ChairChandler");
}

QPair<QString, int> parseArgv(QCoreApplication &a) {
    QCommandLineParser parser;
    initParser(parser, a);

    //turn off console output
    if(!parser.isSet(outputStr)) {
        XmlCout::turnOutputOff();
    }

    //write console output to the log file
    if(XmlLogs *logs; parser.isSet(logsStr)) {
        logs = new XmlLogs(parser.value(logsStr));
        QObject::connect(&a, &QCoreApplication::aboutToQuit, logs, [&logs](){delete logs;});
    }

    //change default reply timeout
    if(bool ok; parser.isSet(timeoutStr)) {
        FTPconnectionWorker::setTimeoutMs(parser.value(timeoutStr).toInt(&ok));
        if(!ok) {
            throw std::runtime_error("Invalid timeout number.");
        }
    }

    //change default root directory
    if(QUrl url; parser.isSet(rootStr)) {
        url = parser.value(rootStr);

        if(url.isValid()) {
            AccountInfo::setDefaultRootPath(url.toString());
        } else {
            throw std::runtime_error("Invalid root path.");
        }
    }

    if(parser.isSet(authorStr)) {
        if(!QDesktopServices::openUrl(QUrl("https://github.com/ChairChandler"))) {
            QTextStream(stderr) << "Cannot open Url: https://github.com/ChairChandler." << endl;
        } else {
            a.exit(EXIT_SUCCESS);
        }
    }

    if(parser.isSet(standardStr)) {
        if(!QDesktopServices::openUrl(QUrl("https://tools.ietf.org/html/rfc959"))) {
            QTextStream(stderr) << "Cannot open Url: https://tools.ietf.org/html/rfc959." << endl;
        } else {
            a.exit(EXIT_SUCCESS);
        }
    }

    QStringList args = parser.positionalArguments();
    QString ip = args.at(0);
    int port = args.at(1).toInt();

    return QPair<QString, int>(ip, port);
}

void initParser(QCommandLineParser &parser, QCoreApplication &a) {
    parser.setApplicationDescription("A simple FTP server compatible with RFC 959.");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("ip", "FTP server ip.", "<ip>");
    parser.addPositionalArgument("port", "FTP server port.", "<port>");

    QCommandLineOption output(QStringList() << outputChar << outputStr, "Show output.");
    QCommandLineOption logs(QStringList() << logsChar << logsStr, "Write logs to the selected file.", "file");
    QCommandLineOption timeout(QStringList() << timeoutChar << timeoutStr, "Change default time for reply.", "miliseconds");
    QCommandLineOption rootPath(QStringList() << rootChar << rootStr, "Change default root path.", "directory");
    QCommandLineOption author(QStringList() << authorChar << authorStr, "Information about author.");
    QCommandLineOption standard(QStringList() << standardChar << standardStr, "FTP server standard.");

    parser.addOption(output);
    parser.addOption(logs);
    parser.addOption(timeout);
    parser.addOption(rootPath);
    parser.addOption(author);
    parser.addOption(standard);

    parser.process(a);
}
