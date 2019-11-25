#include "streammode.h"

bool StreamMode::operator==(Mode &mode) {
    if(dynamic_cast<StreamMode*>(&mode)) {
        return true;
    } else {
        return false;
    }
}
