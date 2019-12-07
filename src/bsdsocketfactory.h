#ifndef BSDSOCKETFACTORY_H
#define BSDSOCKETFACTORY_H
#pragma GCC diagnostic ignored "-Wdeprecated"

#include <arpa/inet.h>
#include <netinet/ip.h>
#include <unistd.h>

class BsdSocketFactory {

    public:
        virtual int socket(int __domain, int __type, int __protocol) = 0;
        virtual int connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) = 0;
        virtual ssize_t write(int __fd, const void *__buf, size_t __n) = 0;
        virtual ssize_t read(int __fd, void *__buf, size_t __nbytes) = 0;
        virtual int bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) = 0;
        virtual int listen(int __fd, int __n) = 0;
        virtual int accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) = 0;
        virtual int close (int __fd) = 0;
        virtual BsdSocketFactory* clone() const {
            return doClone();
        }
        virtual ~BsdSocketFactory();

    protected:
        virtual BsdSocketFactory* doClone() const = 0;
};

class BsdSocketFactoryDefault: public BsdSocketFactory {

    public:
        virtual int socket(int __domain, int __type, int __protocol) override {
            return ::socket(__domain, __type, __protocol);
        }
        virtual int connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) override {
            return ::connect(__fd, __addr, __len);
        }
        virtual ssize_t write(int __fd, const void *__buf, size_t __n) override {
            return ::write(__fd, __buf, __n);
        }
        virtual ssize_t read(int __fd, void *__buf, size_t __nbytes) override {
            return ::read(__fd, __buf, __nbytes);
        }
        virtual int bind(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) override {
            return ::bind(__fd, __addr, __len);
        }
        virtual int listen(int __fd, int __n) override {
            return ::listen(__fd, __n);
        }
        virtual int accept(int __fd, __SOCKADDR_ARG __addr, socklen_t *__restrict __addr_len) override {
            return ::accept(__fd, __addr, __addr_len);
        }
        virtual int close (int __fd) override {
            return ::close(__fd);
        }
        virtual BsdSocketFactory* doClone() const override {
            return new BsdSocketFactoryDefault(*this);
        }
        virtual ~BsdSocketFactoryDefault() override;
};

#endif // BSDSOCKETFACTORY_H
