#ifndef STRUCTURE_H
#define STRUCTURE_H

class Structure {

    public:
        Structure() = default;
        virtual bool operator==(Structure &structure) = 0;
        virtual ~Structure() = default;
};

#endif // STRUCTURE_H
