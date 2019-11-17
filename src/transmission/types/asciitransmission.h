#ifndef ASCIITRANSMISSION_H
#define ASCIITRANSMISSION_H
#include "transmission.h"

/**
 * @brief Send or receive file through data channel in ASCII chars
 */
class AsciiTransmission: public Transmission {

    public:
        AsciiTransmission();
        virtual bool operator==(Transmission &transmission) override;
};

#endif // ASCIITRANSMISSION_H
