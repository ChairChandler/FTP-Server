#include <QtTest>
#include "test.h"
#include "ftpfilesystem/ftpfilesystem.h"

class FTPfileSystemTest : public QObject
{
    Q_OBJECT
    const QString ROOT_NAME = "root_test";
    const QString ROOT_CHILD_DIR = "root_child_dir";
    const QString NOT_EXISTED_PATH = "/xyz";
    QFileInfo root;
public:
    FTPfileSystemTest();
    ~FTPfileSystemTest();

private slots:
    void init();
    void cleanup();
    void test_init_pathNotExists_resultWrongRootDirPathException();
    void test_init_pathNotDir_resultWrongRootDirPathException();
    void test_printWorkingDirectory_relativePath_resultPrintedRelPath();
    void test_printWorkingDirectory_absolutePath_resultPrintedAbsPath();
    void test_changeWorkingDirectory_pathNotExists_resultFalse();
    void test_changeWorkingDirectory_pathNotDir_resultFalse();
    void test_changeWorkingDirectory_pathIsOverridingRoot_resultFalse();
    void test_changeWorkingDirectoryToParent_rootChild_resultTrue();
    void test_changeWorkingDirectoryToParent_root_resultFalse();
    void test_mkdirWD_dirExists_resultFalse();
    void test_mkdirWD_dirNotExists_resultTrue();
    void test_mkdirRelativeRootPath_dirExists_resultFalse();
    void test_mkdirRelativeRootPath_dirNotExists_resultTrue();
    void test_rmdirWD_dirExists_resultTrue();
    void test_rmdirWD_dirNotExists_resultFalse();
    void test_rmdirRelativeRootPath_dirExists_resultTrue();
    void test_rmdirRelativeRootPath_wrongPath_resultFalse();
    void test_rmdirRelativeRootPath_dirNotExists_resultFalse();

private:
    QFileInfo prepareRootChild(FTPfileSystem &fs);
};

FTPfileSystemTest::FTPfileSystemTest()
{
    QDir(QDir().absolutePath() + QDir::separator() + ROOT_NAME).removeRecursively();
}

FTPfileSystemTest::~FTPfileSystemTest()
{

}

void FTPfileSystemTest::init()
{
    if(!QDir().mkdir(ROOT_NAME)) {
        throw std::runtime_error("Cannot create root dir");
    }

    root = QDir().absolutePath() + QDir::separator() + ROOT_NAME;
}

void FTPfileSystemTest::cleanup()
{
    QString v = root.filePath();
    if(!QDir(root.filePath()).removeRecursively()) {
        throw std::runtime_error("Couldn't deleted root");
    }
}

void FTPfileSystemTest::test_init_pathNotExists_resultWrongRootDirPathException()
{
    QVERIFY_EXCEPTION_THROWN(FTPfileSystem(QFileInfo(NOT_EXISTED_PATH)), FTPfileSystem::WrongRootDirPathException);
}

void FTPfileSystemTest::test_init_pathNotDir_resultWrongRootDirPathException()
{
    QTemporaryFile file;
    file.open();
    file.close();

    QVERIFY_EXCEPTION_THROWN(FTPfileSystem(QFileInfo(file.fileName())), FTPfileSystem::WrongRootDirPathException);
}

void FTPfileSystemTest::test_printWorkingDirectory_relativePath_resultPrintedRelPath()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.printWorkingDirectory(true),
             QDir::separator());
    auto child = prepareRootChild(fs);
    QCOMPARE(fs.printWorkingDirectory(true),
             QDir::separator() + child.fileName());
}

void FTPfileSystemTest::test_printWorkingDirectory_absolutePath_resultPrintedAbsPath()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.printWorkingDirectory(false),
             root.absolutePath() + QDir::separator() + root.fileName());
    auto child = prepareRootChild(fs);
    QCOMPARE(fs.printWorkingDirectory(false),
             child.absolutePath() + QDir::separator() + child.fileName());
}

void FTPfileSystemTest::test_changeWorkingDirectory_pathNotExists_resultFalse()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.changeWorkingDirectory(QFileInfo(NOT_EXISTED_PATH)), false);
}

void FTPfileSystemTest::test_changeWorkingDirectory_pathNotDir_resultFalse()
{
    QFile file(QDir().absolutePath() + QDir::separator() + root.fileName() + QDir::separator() + "file");
    FTPfileSystem fs(root);
    QCOMPARE(fs.changeWorkingDirectory(QFileInfo(file)), false);
}

void FTPfileSystemTest::test_changeWorkingDirectory_pathIsOverridingRoot_resultFalse()
{
    QDir file(QDir().absolutePath() + "dir");
    FTPfileSystem fs(root);
    QCOMPARE(fs.changeWorkingDirectory(QFileInfo(file.absolutePath())), false);
}

void FTPfileSystemTest::test_changeWorkingDirectoryToParent_rootChild_resultTrue()
{
    FTPfileSystem fs(root);
    auto child = prepareRootChild(fs);
    fs.changeWorkingDirectoryToParent();
    QCOMPARE(fs.getActualDir().dirName(), root.fileName());
}

void FTPfileSystemTest::test_changeWorkingDirectoryToParent_root_resultFalse()
{
    FTPfileSystem fs(root);
    auto child = prepareRootChild(fs);
    fs.changeWorkingDirectoryToParent();
    QCOMPARE(fs.changeWorkingDirectoryToParent(), false);
}

void FTPfileSystemTest::test_mkdirWD_dirExists_resultFalse()
{
    FTPfileSystem fs(root);
    QDir(root.absolutePath() + QDir::separator() + root.fileName()).mkdir(ROOT_CHILD_DIR);
    QCOMPARE(fs.mkdirWD(ROOT_CHILD_DIR), false);
}

void FTPfileSystemTest::test_mkdirWD_dirNotExists_resultTrue()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.mkdirWD(ROOT_CHILD_DIR), true);
}

void FTPfileSystemTest::test_mkdirRelativeRootPath_dirExists_resultFalse()
{
    FTPfileSystem fs(root);
    QDir(root.absolutePath() + QDir::separator() + root.fileName()).mkdir(ROOT_CHILD_DIR);
    QCOMPARE(fs.mkdirRelativeRootPath(QDir::separator() + ROOT_CHILD_DIR), false);
}

void FTPfileSystemTest::test_mkdirRelativeRootPath_dirNotExists_resultTrue()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.mkdirRelativeRootPath(QDir::separator() + ROOT_CHILD_DIR), true);
}

void FTPfileSystemTest::test_rmdirWD_dirExists_resultTrue()
{
    FTPfileSystem fs(root);
    QDir(root.absolutePath() + QDir::separator() + root.fileName()).mkdir(ROOT_CHILD_DIR);
    QCOMPARE(fs.rmdirWD(ROOT_CHILD_DIR), true);
}

void FTPfileSystemTest::test_rmdirWD_dirNotExists_resultFalse()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.rmdirWD(ROOT_CHILD_DIR), false);
}

void FTPfileSystemTest::test_rmdirRelativeRootPath_dirExists_resultTrue()
{
    FTPfileSystem fs(root);
    QDir(root.absolutePath() + QDir::separator() + root.fileName()).mkdir(ROOT_CHILD_DIR);
    QCOMPARE(fs.rmdirRelativeRootPath(QDir::separator() + ROOT_CHILD_DIR), true);
}

void FTPfileSystemTest::test_rmdirRelativeRootPath_wrongPath_resultFalse()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.rmdirRelativeRootPath(QDir::separator() + ROOT_CHILD_DIR), false);
}

void FTPfileSystemTest::test_rmdirRelativeRootPath_dirNotExists_resultFalse()
{
    FTPfileSystem fs(root);
    QCOMPARE(fs.rmdirRelativeRootPath(NOT_EXISTED_PATH + NOT_EXISTED_PATH), false);
}

QFileInfo FTPfileSystemTest::prepareRootChild(FTPfileSystem &fs)
{
    QString path = root.absolutePath() + QDir::separator() +
            root.fileName() + QDir::separator() + ROOT_CHILD_DIR;

    fs.actualDir = QDir(path);
    return QFileInfo(path);
}

QTEST_APPLESS_MAIN(FTPfileSystemTest)

#include "tst_ftpfilesystemtest.moc"
