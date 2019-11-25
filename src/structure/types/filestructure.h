#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include "structure/structure.h"

class FileStructure: public Structure {

    public:
        FileStructure() = default;
        virtual bool operator==(Structure &structure) override;
        virtual ~FileStructure() override = default;
};

#endif // FILESTRUCTURE_H
