#include "transmission.h"
#include <unistd.h>

void Transmission::send(int dataChannelSocket, QFile &file) {

    for(const QString data: fileRead(file)) {
        std::copy(data.begin(), data.end(), buffer);
        write(dataChannelSocket, buffer.data(), buffer.size());
    }

    write(dataChannelSocket, EOF_BYTES.data(), EOF_BYTES.size());
}

void Transmission::receive(int dataChannelSocket, QFile &file) {

    //read(dataChannelSocket, buffer.data(), buffer.size());
}
