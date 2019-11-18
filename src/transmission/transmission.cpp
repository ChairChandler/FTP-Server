#include "transmission.h"
#include <unistd.h>

Transmission::Transmission(TransmissionReaderInterface &reader, TransmissionWriterInterface &writer): reader(reader), writer(writer) {

}

void Transmission::send(int dataChannelSocket, QFile &file) {
    try {
        reader.init(file);
    } catch (TransmissionReaderInterface::FileOpeningException &e) {
        throw e;
    }

    while(!reader.isEndOfFile()) {
        Buffer &buffer = reader.readDataPortion();

        size_t i = 0;
        for(QChar q: buffer) {
            localBuff[i++] = q.toLatin1();
        }

        write(dataChannelSocket, localBuff.data(), localBuff.size());
    }

    reader.cleanUp();
    write(dataChannelSocket, EOF_BYTES.data(), EOF_BYTES.size());
}

void Transmission::receive(int dataChannelSocket, QFile &file) {
    writer.init(file);

    Buffer buffer;
    bool endOfTransmission = false;

    do{
        read(dataChannelSocket, localBuff.data(), localBuff.size());

        if(containsEOF()) {
            deleteEOF();
            endOfTransmission = true;
        }

        size_t i = 0;
        for(char c: localBuff) {
            buffer[i++] = c;
        }

        writer.writeDataPortion(buffer);
    }while(!endOfTransmission);

    writer.cleanUp();
}

bool Transmission::containsEOF() {
    for(size_t i=0; i <localBuff.size(); i++) {

        for(size_t j=i; j<localBuff.size() && (j-i)<=EOF_BYTES.size(); j++) {
            if((j-i) == EOF_BYTES.size()) {
                eofStart = i;
                eofStop = j;
                return true;
            } else if(localBuff[j] != EOF_BYTES[j-i]) {
                break;
            }
        }
    }

    return false;
}

void Transmission::deleteEOF() {
    for(size_t i=eofStart; i<eofStop; i++) {
        localBuff[i] = '\0';
    }
}
