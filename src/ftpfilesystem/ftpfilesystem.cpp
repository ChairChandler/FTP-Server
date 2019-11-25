#include "ftpfilesystem.h"
#include <QRegExp>

FTPfileSystem::FTPfileSystem(const QFileInfo &beginUserFileSpace) {
    if(beginUserFileSpace.exists() && beginUserFileSpace.isDir()) {
        rootDir = QDir(beginUserFileSpace.absolutePath() + QDir::separator() + beginUserFileSpace.fileName());
        actualDir = rootDir;
    } else {
        throw WrongRootDirPathException();
    }
}

QString FTPfileSystem::printWorkingDirectory(bool relativePath) const {
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

bool FTPfileSystem::changeWorkingDirectory(const QFileInfo &dir) {
    QRegExp r("^" + rootDir.path() + QDir::separator());
    if(r.indexIn(dir.path()) == -1 || !actualDir.cd(dir.path())) {
        return false;
    }
    return true;
}

bool FTPfileSystem::changeWorkingDirectoryToParent() {
    if(rootDir == actualDir.absolutePath() || !actualDir.cdUp()) {
        return false;
    }
    return true;
}

bool FTPfileSystem::mkdirWD(const QString &name) {
    if(!actualDir.mkdir(name)) {
        return false;
    }
    return true;
}

bool FTPfileSystem::mkdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(QDir(dirPath).exists() || !QDir().mkpath(dirPath)) {
        return false;
    }
    return true;
}

bool FTPfileSystem::rmdirWD(const QString &name) {
    if(!actualDir.rmdir(name)) {
        return false;
    }
    return true;
}

bool FTPfileSystem::rmdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(!QDir(dirPath).exists() || !QDir().rmpath(rootDir.absolutePath() + path)) {
        return false;
    }
    return true;
}

QList<QFileInfo> FTPfileSystem::getFilesInfoInWorkingDirectory() const {
    return actualDir.entryInfoList();
}

QDir FTPfileSystem::getRootDir() const {
    return rootDir;
}

QDir FTPfileSystem::getActualDir() const {
    return actualDir;
}

FTPfileSystem::~FTPfileSystem() {

}
