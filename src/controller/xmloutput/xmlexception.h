#ifndef XMLEXCEPTION_H
#define XMLEXCEPTION_H

#include <QString>
#include <exception>
#include <QTextStream>
#include "xmlmessage.h"

/**
* @brief Creates exception in XML style.
*/
class XmlException: public XmlMessage, public std::runtime_error {

    private:
        static inline bool outputOn = true;
        using XmlMessage::getMessage;
        static inline auto cout = QTextStream(stdout);
        static inline auto outStreams = QList<QTextStream*>();

    public:
        /**
        * @param tag Custom XML tag.
        */
        explicit XmlException(const QString &tag);
        XmlException& key(const QString &key) override;
        XmlException& value(const QString &value) override;
        XmlException& end();

        static void turnOutputOff();
        static void turnOutputOn();
        static void addStream(const QTextStream &stream);
        virtual const char* what() const noexcept override;

        void print();
};

#endif // XMLEXCEPTION_H
