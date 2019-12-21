#ifndef FTPFILESYSTEM_H
#define FTPFILESYSTEM_H

#include <QFileInfo>
#include <QDir>
#include "exception/namedexception.h"

/**
* @brief Interface for handle virtual filesystem designed for ftp server.
* @interface
*/
class InterfaceFTPfileSystem {

    public:
        virtual QString printWorkingDirectory(bool relativePath) const = 0;
        virtual bool changeAbsoluteWorkingDirectory(const QString &path) = 0;
        virtual bool changeRelativeRootWorkingDirectory(const QString &path) = 0;
        virtual bool changeRelativeCurrentWorkingDirectory(const QString &path) = 0;
        virtual bool changeWorkingDirectoryToParent() = 0;
        virtual bool mkdirWD(const QString &name) = 0;
        virtual bool mkdirRelativeRootPath(const QString &path) = 0;
        virtual bool rmdirWD(const QString &name) = 0;
        virtual bool rmdirRelativeRootPath(const QString &path) = 0;
        virtual QStringList getLinuxFilesInfoListInWorkingDirectory() = 0;
        virtual QStringList getLinuxFilesInfoListInRelativePath(const QString &path) = 0;
        virtual QDir getRootDir() const = 0;
        virtual QDir getActualDir() const = 0;
        virtual ~InterfaceFTPfileSystem() = default;

        struct WrongRootDirPathException: public NamedException {
            virtual const char* what() const noexcept override {
                return "Root dir path invalid.";
            }
            virtual QString name() override {
                return "WrongRootDirPathException";
            }
        };
};

/**
* @brief Default implementation of ftp filesystem interface, provide private user file space.
*/
class FTPfileSystemDefault: public InterfaceFTPfileSystem {

    private:
        QDir rootDir, actualDir;

        QString runLs(const QString &path);
        QStringList getLinuxFilesInfoListInAbsolutePath(const QString &path);

    public:
        FTPfileSystemDefault(const QFileInfo &beginUserFileSpace);

        virtual QString printWorkingDirectory(bool relativePath) const override;
        virtual bool changeAbsoluteWorkingDirectory(const QString &path) override;
        virtual bool changeRelativeRootWorkingDirectory(const QString &path) override;
        virtual bool changeRelativeCurrentWorkingDirectory(const QString &path) override;
        virtual bool changeWorkingDirectoryToParent() override;
        virtual bool mkdirWD(const QString &name) override;
        virtual bool mkdirRelativeRootPath(const QString &path) override;
        virtual bool rmdirWD(const QString &name) override;
        virtual bool rmdirRelativeRootPath(const QString &path) override;
        virtual QStringList getLinuxFilesInfoListInWorkingDirectory() override;
        virtual QStringList getLinuxFilesInfoListInRelativePath(const QString &path) override;
        virtual QDir getRootDir() const override;
        virtual QDir getActualDir() const override;
};

#endif // FTPFILESYSTEM_H
