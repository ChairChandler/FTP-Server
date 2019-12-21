#include "xmllogs.h"
#include "xmlcout.h"
#include "xmlexception.h"

XmlLogs::XmlLogs(const QString &fileName): file(fileName) {
    using Flags = QFile::OpenModeFlag;
    if(file.open(QFile::OpenMode(Flags::Text|Flags::Append))) {
        stream = new QTextStream(&file);
        XmlCout::addStream(*stream);
        XmlException::addStream(*stream);
    } else {
        throw std::runtime_error(QString("Cannot write logs to the file %1.").arg(fileName).toLatin1());
    }
}

XmlLogs::~XmlLogs() {
    delete stream;
    file.close();
}

