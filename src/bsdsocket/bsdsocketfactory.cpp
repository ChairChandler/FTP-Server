#include "bsdsocketfactory.h"

int BsdSocketFactoryDefault::socket(int __domain, int __type, int __protocol) {
    return ::socket(__domain, __type, __protocol);
}

int BsdSocketFactoryDefault::connect(int __fd, const sockaddr *__addr, socklen_t __len) {
    return ::connect(__fd, __addr, __len);
}

ssize_t BsdSocketFactoryDefault::write(int __fd, const void *__buf, size_t __n) {
    return ::write(__fd, __buf, __n);
}

ssize_t BsdSocketFactoryDefault::read(int __fd, void *__buf, size_t __nbytes) {
    return ::read(__fd, __buf, __nbytes);
}

int BsdSocketFactoryDefault::bind(int __fd, const sockaddr *__addr, socklen_t __len) {
    return ::bind(__fd, __addr, __len);
}

int BsdSocketFactoryDefault::listen(int __fd, int __n) {
    return ::listen(__fd, __n);
}

int BsdSocketFactoryDefault::accept(int __fd, sockaddr *__addr, socklen_t *__addr_len) {
    return ::accept(__fd, __addr, __addr_len);
}

int BsdSocketFactoryDefault::close(int __fd) {
    return ::close(__fd);
}

int BsdSocketFactoryDefault::getsockopt(int __fd, int __level, int __optname, void *__optval, socklen_t *__optlen) {
    return ::getsockopt(__fd, __level, __optname, __optval, __optlen);
}

InterfaceBsdSocketFactory *BsdSocketFactoryDefault::doClone() const {
    return new BsdSocketFactoryDefault(*this);
}
