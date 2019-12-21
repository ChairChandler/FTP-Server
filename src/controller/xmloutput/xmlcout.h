#ifndef XMLCOUT_H
#define XMLCOUT_H

#include <QTextStream>
#include "xmlmessage.h"

/**
* @brief Print informations in XML style.
*/
class XmlCout: public XmlMessage {

    private:
        static inline bool outputOn = true;
        static inline auto cout = QTextStream(stdout);
        static inline auto outStreams = QList<QTextStream*>();
        using XmlMessage::end;
        using XmlMessage::getMessage;

    public:
        /**
        * @param tag Custom XML tag.
        */
        explicit XmlCout(const QString &tag);
        static void turnOutputOff();
        static void turnOutputOn();
        static void addStream(const QTextStream &stream);
        ~XmlCout();
};

#endif // XMLCOUT_H
