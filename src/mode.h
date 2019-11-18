#ifndef MODE_H
#define MODE_H

class Mode {

    public:
        Mode() = default;
        virtual bool operator==(Mode &mode) = 0;
        virtual ~Mode() = default;
};

#endif // MODE_H
