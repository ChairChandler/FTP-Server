#ifndef STREAMMODE_H
#define STREAMMODE_H

#include "mode/mode.h"

class StreamMode: public Mode {

    public:
        StreamMode() = default;
        virtual bool operator==(Mode &mode) override;
        virtual ~StreamMode() override = default;
};

#endif // STREAMMODE_H
