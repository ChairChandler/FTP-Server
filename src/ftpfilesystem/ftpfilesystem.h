#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H

#include <QFileInfo>
#include <QDir>

class FTPfileSystem {

    public:
        virtual QString printWorkingDirectory(bool relativePath) const = 0;
        virtual bool changeWorkingDirectory(const QFileInfo &dir) = 0;
        virtual bool changeWorkingDirectoryToParent() = 0;
        virtual bool mkdirWD(const QString &name) = 0;
        virtual bool mkdirRelativeRootPath(const QString &path) = 0;
        virtual bool rmdirWD(const QString &name) = 0;
        virtual bool rmdirRelativeRootPath(const QString &path) = 0;
        virtual QList<QFileInfo> getFilesInfoInWorkingDirectory() const = 0;
        virtual QDir getRootDir() const = 0;
        virtual QDir getActualDir() const = 0;
        virtual ~FTPfileSystem();

        struct WrongRootDirPathException: std::exception {};
};

class FTPfileSystemImpl: public FTPfileSystem {

    private:
        QDir rootDir, actualDir;

    public:
        FTPfileSystemImpl(const QFileInfo &beginUserFileSpace);
        virtual QString printWorkingDirectory(bool relativePath) const override;
        virtual bool changeWorkingDirectory(const QFileInfo &dir) override;
        virtual bool changeWorkingDirectoryToParent() override;
        virtual bool mkdirWD(const QString &name) override;
        virtual bool mkdirRelativeRootPath(const QString &path) override;
        virtual bool rmdirWD(const QString &name) override;
        virtual bool rmdirRelativeRootPath(const QString &path) override;
        virtual QList<QFileInfo> getFilesInfoInWorkingDirectory() const override;
        virtual QDir getRootDir() const override;
        virtual QDir getActualDir() const override;
        virtual ~FTPfileSystemImpl() override;

        struct WrongRootDirPathException: std::exception {};
};

#endif // FTPFILESYSTEM_H
