#ifndef FILELOCKER_H
#define FILELOCKER_H

#include <QBasicMutex>
#include <QList>
#include <QFileInfo>
#include "account/accountinfo.h"

/**
* @brief Lock files from being deleted/modified by transmission or rmdir command.
*/
class FileLocker {

    private:
        using RelativeRootPath = QString;
        using DirBool = bool;
        using FileLockInfo = std::tuple<QString, DirBool, int>;
        static inline auto fileMutex = QBasicMutex();
        static inline auto openedFiles = QList<FileLockInfo>();

        static const inline auto rootDir = AccountInfo::getDefaultRootPath();

        static QString extractRelativeRootPath(const QFileInfo &file);
        static bool fileDir(const QString &pathLockFile, const QString &pathOpenFile, bool openFileDir);
        static bool fileNotDir(const QString &pathLockFile, const QString &pathOpenFile, bool openFileDir);

    public:
        /**
        * @brief Lock file from read/write/delete.
        * @param lockFile File to be locked.
        * @return True if file is locked.
        */
        static bool tryHardLockFile(const QFileInfo &lockFile);
        /**
        * @brief Unlock file for read/write/delete.
        * @param lockFile File which is locked by tryHardLockFile method.
        */
        static void hardUnLockFile(const QFileInfo &lockFile);
        /**
        * @brief Lock file from write/delete.
        * @param lockFile File to be locked.
        * @return True if file is locked.
        */
        static bool trySoftLockFile(const QFileInfo &lockFile);
        /**
        * @brief Unlock file for write/delete.
        * @param lockFile File which is locked by trySoftLockFile method.
        */
        static void softUnLockFile(const QFileInfo &lockFile);
};

#endif // FILELOCKER_H
