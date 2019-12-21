#ifndef NAMEDEXCEPTION_H
#define NAMEDEXCEPTION_H

#include <exception>
#include <QString>

/**
* @brief Exception with typename.
*/
class NamedException: public std::exception {

    public:
        NamedException();
        virtual QString name();
};

#endif // NAMEDEXCEPTION_H
