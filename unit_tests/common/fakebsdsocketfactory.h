#ifndef FAKEBSDSOCKETFACTORY_H
#define FAKEBSDSOCKETFACTORY_H

#include "fakeit.hpp"
#include "bsdsocketfactory.h"
using namespace fakeit;

class FakeBsdSocketFactory: public BsdSocketFactory {
    static inline Mock<BsdSocketFactory> *mock;

public:
    static void setMock(Mock<BsdSocketFactory> &newMock) {
        mock = &newMock;
    }

    virtual int socket(int __domain, int __type, int __protocol) override {
        return mock->get().socket(__domain, __type, __protocol);
    }
    virtual int connect(int __fd, __CONST_SOCKADDR_ARG __addr, socklen_t __len) override {
        return mock->get().connect(__fd, __addr, __len);
    }
    virtual ssize_t write(int __fd, const void *__buf, size_t __n) override {
        return mock->get().write(__fd, __buf, __n);
    }
    virtual ssize_t read(int __fd, void *__buf, size_t __nbytes) override {
        return mock->get().read(__fd, __buf, __nbytes);
    }
    virtual ~FakeBsdSocketFactory() override;

protected:
    virtual BsdSocketFactory* doClone() const override {
        return new FakeBsdSocketFactory(*this);
    }
};

#endif // FAKEBSDSOCKETFACTORY_H
