#include "ftpfilesystem.h"
#include "transmission/filetransmission.h"
#include "filelocker.h"
#include <QRegExp>
#include <QProcess>

FTPfileSystemDefault::FTPfileSystemDefault(const QFileInfo &beginUserFileSpace) {
    if(beginUserFileSpace.exists() && beginUserFileSpace.isDir()) {
        rootDir = QDir(beginUserFileSpace.absoluteFilePath());
        actualDir = rootDir;
    } else {
        throw WrongRootDirPathException();
    }
}

QString FTPfileSystemDefault::printWorkingDirectory(bool relativePath) const {
    QString path;

    if(relativePath) {
        path = actualDir.absolutePath().remove(rootDir.absolutePath());
    } else {
        path = actualDir.absolutePath();
    }

    if(path == "") {
        path = "/";
    }

    return path;
}

bool FTPfileSystemDefault::changeAbsoluteWorkingDirectory(const QString &path) {
    QRegExp r("^" + rootDir.path() + QDir::separator());
    if(r.indexIn(path) == -1 || !actualDir.cd(path)) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::changeRelativeRootWorkingDirectory(const QString &path) {
    if(!actualDir.cd(rootDir.absolutePath() + path)) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::changeRelativeCurrentWorkingDirectory(const QString &path) {
    if(!actualDir.cd(actualDir.absolutePath() + QDir::separator() + path)) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::changeWorkingDirectoryToParent() {
    if(rootDir.absolutePath() == actualDir.absolutePath() || !actualDir.cdUp()) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::mkdirWD(const QString &name) {
    if(!actualDir.mkdir(name)) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::mkdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(QDir(dirPath).exists() || !QDir().mkpath(dirPath)) {
        return false;
    } else {
        return true;
    }
}

bool FTPfileSystemDefault::rmdirWD(const QString &name) {
    QString dirAbsPath = actualDir.absolutePath() + QDir::separator() + name;
    if(!FileLocker::tryHardLockFile(dirAbsPath)) {
        throw InterfaceTransmissionFileAccess::FileOpeningException();
    }

    if(!QDir(actualDir.filePath(name)).removeRecursively()) {
        FileLocker::hardUnLockFile(dirAbsPath);
        return false;
    } else {
        FileLocker::hardUnLockFile(dirAbsPath);
        return true;
    }
}

bool FTPfileSystemDefault::rmdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(!FileLocker::tryHardLockFile(path)) {
        throw InterfaceTransmissionFileAccess::FileOpeningException();
    }

    if(!QDir(dirPath).exists() || !QDir().rmpath(rootDir.absolutePath() + path)) {
        FileLocker::hardUnLockFile(path);
        return false;
    } else {
        FileLocker::hardUnLockFile(path);
        return true;
    }
}

QString FTPfileSystemDefault::runLs(const QString &path) {
    QByteArray lsOutput;

    QProcess p;

    p.setWorkingDirectory(path);
    p.start("ls", QStringList() << "-l" << "-a");

    p.waitForFinished(-1);

    return p.readAllStandardOutput();
}

QStringList FTPfileSystemDefault::getLinuxFilesInfoListInAbsolutePath(const QString &path) {
    auto splitBytes = runLs(path).split('\n');

    QStringList filesInfo;
    for(QString s: splitBytes) {
        filesInfo << QString::fromStdString(s.toStdString()) + "\r\n";
    }

    filesInfo.removeFirst();
    filesInfo.removeLast();

    return filesInfo;
}

QStringList FTPfileSystemDefault::getLinuxFilesInfoListInWorkingDirectory() {
    return getLinuxFilesInfoListInAbsolutePath(actualDir.path());
}

QStringList FTPfileSystemDefault::getLinuxFilesInfoListInRelativePath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;
    return getLinuxFilesInfoListInAbsolutePath(dirPath);
}

QDir FTPfileSystemDefault::getRootDir() const {
    return rootDir;
}

QDir FTPfileSystemDefault::getActualDir() const {
    return actualDir;
}
