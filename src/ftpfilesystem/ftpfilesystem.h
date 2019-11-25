#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H

#include <QFileInfo>
#include <QDir>

class FTPfileSystem {

    private:
        QDir rootDir, actualDir;

    public:
        FTPfileSystem(const QFileInfo &beginUserFileSpace);
        QString printWorkingDirectory(bool relativePath) const;
        bool changeWorkingDirectory(const QFileInfo &dir);
        bool changeWorkingDirectoryToParent();
        bool mkdirWD(const QString &name);
        bool mkdirRelativeRootPath(const QString &path);
        bool rmdirWD(const QString &name);
        bool rmdirRelativeRootPath(const QString &path);
        QList<QFileInfo> getFilesInfoInWorkingDirectory() const;
        QDir getRootDir() const;
        QDir getActualDir() const;
        ~FTPfileSystem();

        struct WrongRootDirPathException: std::exception {};
};

#endif // FTPFILESYSTEM_H
