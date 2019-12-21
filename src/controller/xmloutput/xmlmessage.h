#ifndef XMLMESSAGE_H
#define XMLMESSAGE_H

#include <QString>

/**
* @brief Creates informations in XML style. Each message have to ended by end method.
*/
class XmlMessage {

    private:
        const QString elementBegin = "<";
        const QString elementEnd = "/>";
        QString message;

    public:
        /**
        * @param tag Custom XML tag.
        */
        explicit XmlMessage(const QString &tag);

        /**
        * @param key Custom XML attribute.
        */
        virtual XmlMessage& key(const QString &key);
        /**
        * @param value Custom XML value.
        */
        virtual XmlMessage& value(const QString &value);
        /**
        * @brief End of XML message.
        */
        void end();

        QString getMessage() const;

        virtual ~XmlMessage() = default;
};

#endif // XMLMESSAGE_H
