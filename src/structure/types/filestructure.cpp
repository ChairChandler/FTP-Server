#include "filestructure.h"

bool FileStructure::operator==(Structure &structure) {
    if(dynamic_cast<FileStructure*>(&structure)) {
        return true;
    } else {
        return false;
    }
}
