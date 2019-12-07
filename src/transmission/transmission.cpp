#include "transmission.h"

Transmission::Transmission(TransmissionReaderInterface &reader, TransmissionWriterInterface &writer): reader(reader), writer(writer) {

}

void Transmission::send(int dataChannelSocket, QFile &file) {
    try {
        reader.init(file);
    } catch (TransmissionReaderInterface::FileOpeningException &e) {
        throw e;
    }

    forever {
        auto [buffer, size] = reader.readDataPortion();

        copyConverted(buffer, localBuff);
        write(dataChannelSocket, localBuff.data(), size);

        if(size < BUFF_SIZE) {
            break;
        }
    }

    reader.cleanUp();
    bsdSocketFactory->write(dataChannelSocket, EOF_BYTES.data(), EOF_BYTES.size());
}

void Transmission::receive(int dataChannelSocket, QFile &file) {
    writer.init(file);

    using DataTransmission = TransmissionFileAccessInterface;
    DataTransmission::data_size size = BUFF_SIZE;
    ExternalBuffer buffer;
    bool endOfTransmission = false;

    do{
        bsdSocketFactory->read(dataChannelSocket, localBuff.data(), localBuff.size());

        if(containsEOF()) {
            endOfTransmission = true;
            size = eofStart;
        }

        copyConverted(localBuff, buffer);

        DataTransmission::BufferInfo info(buffer, size);
        writer.writeDataPortion(info);
    }while(!endOfTransmission);

    writer.cleanUp();
}

void Transmission::setBsdSocketFactory(const BsdSocketFactory &newFactory) {
    bsdSocketFactory = FactoryRef(newFactory.clone());
}

void Transmission::copyConverted(std::array<QChar, Transmission::BUFF_SIZE> &src, std::array<char, Transmission::BUFF_SIZE> &dst) {
    size_t i = 0;
    for(QChar c: src) {
       dst[i++] = c.toLatin1();
    }
}

void Transmission::copyConverted(std::array<char, Transmission::BUFF_SIZE> &src, std::array<QChar, Transmission::BUFF_SIZE> &dst) {
    size_t i = 0;
    for(char c: src) {
        dst[i++] = c;
    }
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

size_t Transmission::getBuffSize(){
    return BUFF_SIZE;
}
