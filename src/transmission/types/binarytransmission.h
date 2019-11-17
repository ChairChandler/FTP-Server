#ifndef BINARYTRANSMISSION_H
#define BINARYTRANSMISSION_H
#include "transmission.h"

/**
 * @brief Send or receive file through data channel in binary chars
 */
class BinaryTransmission: public Transmission {

    public:
        BinaryTransmission();
        virtual bool operator==(Transmission &transmission) override;
};

#endif // BINARYTRANSMISSION_H
