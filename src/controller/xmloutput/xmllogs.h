#ifndef XMLLOGS_H
#define XMLLOGS_H

#include <QString>
#include <QFile>
#include <QTextStream>

/**
* @brief Add log stream to the XmlException and XmlCout classes.
*/
class XmlLogs: public QObject {

    private:
        Q_OBJECT
        QFile file;
        QTextStream *stream;

    public:
        XmlLogs(const XmlLogs&);
        /**
        * @param fileName Name of the file where logs will be wrote
        */
        XmlLogs(const QString &fileName);
        ~XmlLogs();
};

#endif // XMLLOGS_H
