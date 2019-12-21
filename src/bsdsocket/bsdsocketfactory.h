#ifndef BSDSOCKETFACTORY_H
#define BSDSOCKETFACTORY_H

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

/**
* @brief Interface for bsd sockets factory.
* @interface
*/
class InterfaceBsdSocketFactory {

    protected:
        virtual InterfaceBsdSocketFactory* doClone() const = 0;

    public:
        virtual int socket(int __domain, int __type, int __protocol) = 0;
        virtual int connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) = 0;
        virtual ssize_t write(int __fd, const void *__buf, size_t __n) = 0;
        virtual ssize_t read(int __fd, void *__buf, size_t __nbytes) = 0;
        virtual int bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) = 0;
        virtual int listen(int __fd, int __n) = 0;
        virtual int accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) = 0;
        virtual int close (int __fd) = 0;
        virtual int getsockopt (int __fd, int __level, int __optname, void *__restrict __optval, socklen_t *__restrict __optlen) = 0;
        virtual InterfaceBsdSocketFactory* clone() const {
            return doClone(); //its needed in C++ in cause of not allowing to copy derived class passed by interface
        }
        virtual ~InterfaceBsdSocketFactory() = default;
};

/**
* @brief Default implementation of bsd socket factory interface.
*/
class BsdSocketFactoryDefault: public InterfaceBsdSocketFactory {

    public:
        virtual int socket(int __domain, int __type, int __protocol) override;
        virtual int connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) override;
        virtual ssize_t write(int __fd, const void *__buf, size_t __n) override;
        virtual ssize_t read(int __fd, void *__buf, size_t __nbytes) override;
        virtual int bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) override;
        virtual int listen(int __fd, int __n) override;
        virtual int accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) override;
        virtual int close (int __fd) override;
        virtual int getsockopt (int __fd, int __level, int __optname, void *__restrict __optval, socklen_t *__restrict __optlen) override;
        virtual InterfaceBsdSocketFactory* doClone() const override;
};

#endif // BSDSOCKETFACTORY_H
