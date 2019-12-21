#include "filelocker.h"
#include "account/accountinfo.h"
#include <QRegExp>

bool FileLocker::tryHardLockFile(const QFileInfo &lockFile) {

    QMutexLocker lock(&fileMutex);
    QString pathLockFile = extractRelativeRootPath(lockFile);

    for(auto [pathOpenFile, isDir, _]: openedFiles) {
        Q_UNUSED(_)
        if(lockFile.isDir() && !fileDir(pathLockFile, pathOpenFile, isDir)) {
            return false;
        } else if(!fileNotDir(pathLockFile, pathOpenFile, isDir)){
            return false;
        }
    }

    openedFiles << FileLockInfo(pathLockFile, lockFile.isDir(), -1);
    return true;
}

void FileLocker::hardUnLockFile(const QFileInfo &lockFile) {

    QMutexLocker lock(&fileMutex);
    QString pathLockFile = extractRelativeRootPath(lockFile);

    auto iter = std::remove_if(openedFiles.begin(), openedFiles.end(),
                               [&pathLockFile](auto info){return std::get<0>(info) == pathLockFile;});

    openedFiles.erase(iter);
}

bool FileLocker::trySoftLockFile(const QFileInfo &lockFile) {

    if(lockFile.isDir()) {
        return false;
    }

    QMutexLocker lock(&fileMutex);
    QString pathLockFile = extractRelativeRootPath(lockFile);

    for(auto &[pathOpenFile, isDir, accessCounter]: openedFiles) {

        /*
         * If open file is file and has same path as lock file and is locked from read/write/delete,
         * then we return false. (fail)
         * Otherwise file is locked from write/delete then we increment counter and return true. (success)
         *
         * If open file is directory and has partial common absolute path and is locked then we return false. (fail)
         */

        //File & File
        if(!isDir && pathLockFile == pathOpenFile) {
            if(accessCounter == -1) { //hard lock
                return false;
            } else {
                accessCounter++;
                return true;
            }

            //File & Dir
        } else if(QRegExp r("^" + pathOpenFile); isDir && r.indexIn(pathLockFile) > -1) {
            return false;
        }
    }

    openedFiles << FileLockInfo(pathLockFile, lockFile.isDir(), 1);
    return true;
}

void FileLocker::softUnLockFile(const QFileInfo &lockFile) {

    QMutexLocker lock(&fileMutex);
    QString pathLockFile = extractRelativeRootPath(lockFile);

    auto iter = std::remove_if(openedFiles.begin(), openedFiles.end(),
                               [&pathLockFile](auto info)
    {
        if(std::get<0>(info) == pathLockFile) {
            int &accessCounter = std::get<2>(info);
            if(accessCounter > 1) {
                accessCounter--;
                return false;
            } else {
                return true;
            }
        } else {
            return false;
        }
    });

    if(iter != openedFiles.end()) {
        openedFiles.erase(iter);
    }
}

QString FileLocker::extractRelativeRootPath(const QFileInfo &file) {
    return file.absoluteFilePath().remove(rootDir.absoluteFilePath());
}

bool FileLocker::fileDir(const QString &pathLockFile, const QString &pathOpenFile, bool openFileDir) {
    //Dir & File
    if(QRegExp r("^" + pathLockFile); !openFileDir && r.indexIn(pathOpenFile) > -1) {
        return false;

    //Dir & Dir
    } else if(openFileDir) {
        const QString *longerPath, *shorterPath;

        if(pathLockFile.size() >= pathOpenFile.size()) {
            longerPath = &pathLockFile;
            shorterPath = &pathOpenFile;
        } else {
            longerPath = &pathOpenFile;
            shorterPath = &pathLockFile;
        }

        if(QRegExp r("^" + *shorterPath); r.indexIn(*longerPath) > -1) {
            return false;
        }
    }

    return true;
}

bool FileLocker::fileNotDir(const QString &pathLockFile, const QString &pathOpenFile, bool openFileDir) {
    //File & File
    if(!openFileDir && pathLockFile == pathOpenFile) {
        return false;
        //File & Dir
    } else if(QRegExp r("^" + pathOpenFile); openFileDir && r.indexIn(pathLockFile) > -1) {
        return false;
    }

    return true;
}
