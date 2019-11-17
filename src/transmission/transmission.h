#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include <QFile>

class Transmission {

    private:
        std::array<QChar, 1024> buffer;
        std::array<QChar, 2> EOF_BYTES = {0xFF, 2};

    public:
        Transmission() = default;
        void send(int dataChannelSocket, QFile &file);
        void receive(int dataChannelSocket, QFile &file);
        virtual ~Transmission() = default;
        virtual bool operator==(Transmission &transmission) = 0;

    protected:

        class iterator: public std::iterator<std::forward_iterator_tag,     // iterator_category
                                            QString,                        // value_type
                                            QString,                        // difference_type
                                            const QString*,                 // pointer
                                            const QString&>                 // reference
        {
                QString value = "";
            public:
                iterator(long _num = 0) : num(_num) {}
                iterator& operator++() {num = TO >= FROM ? num + 1: num - 1; return *this;}
                iterator operator++(int) {iterator retval = *this; ++(*this); return retval;}
                bool operator==(iterator other) const {return value == other.value;}
                bool operator!=(iterator other) const {return !(*this == other);}
                QString operator*() {return value;}
        };

        virtual QString fileRead(QFile &file) = 0;
        virtual void fileWrite(QFile &file, QString txt) = 0;
};

#endif // TRANSMISSION_H
