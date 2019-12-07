#include "ftpfilesystem.h"
#include <QRegExp>

FTPfileSystemImpl::FTPfileSystemImpl(const QFileInfo &beginUserFileSpace) {
    if(beginUserFileSpace.exists() && beginUserFileSpace.isDir()) {
        rootDir = QDir(beginUserFileSpace.absolutePath() + QDir::separator() + beginUserFileSpace.fileName());
        actualDir = rootDir;
    } else {
        throw WrongRootDirPathException();
    }
}

QString FTPfileSystemImpl::printWorkingDirectory(bool relativePath) const {
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

bool FTPfileSystemImpl::changeWorkingDirectory(const QFileInfo &dir) {
    QRegExp r("^" + rootDir.path() + QDir::separator());
    if(r.indexIn(dir.path()) == -1 || !actualDir.cd(dir.path())) {
        return false;
    }
    return true;
}

bool FTPfileSystemImpl::changeWorkingDirectoryToParent() {
    if(rootDir == actualDir.absolutePath() || !actualDir.cdUp()) {
        return false;
    }
    return true;
}

bool FTPfileSystemImpl::mkdirWD(const QString &name) {
    if(!actualDir.mkdir(name)) {
        return false;
    }
    return true;
}

bool FTPfileSystemImpl::mkdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(QDir(dirPath).exists() || !QDir().mkpath(dirPath)) {
        return false;
    }
    return true;
}

bool FTPfileSystemImpl::rmdirWD(const QString &name) {
    if(!actualDir.rmdir(name)) {
        return false;
    }
    return true;
}

bool FTPfileSystemImpl::rmdirRelativeRootPath(const QString &path) {
    QString dirPath = rootDir.absolutePath() + path;

    if(!QDir(dirPath).exists() || !QDir().rmpath(rootDir.absolutePath() + path)) {
        return false;
    }
    return true;
}

QList<QFileInfo> FTPfileSystemImpl::getFilesInfoInWorkingDirectory() const {
    return actualDir.entryInfoList();
}

QDir FTPfileSystemImpl::getRootDir() const {
    return rootDir;
}

QDir FTPfileSystemImpl::getActualDir() const {
    return actualDir;
}

FTPfileSystemImpl::~FTPfileSystemImpl() {

}

FTPfileSystem::~FTPfileSystem()
{

}
