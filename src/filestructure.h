#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

class FileStructure {

    public:
        FileStructure() = default;
        virtual bool operator==(FileStructure &fileStructure) = 0;
        virtual ~FileStructure() = default;
};

#endif // FILESTRUCTURE_H
