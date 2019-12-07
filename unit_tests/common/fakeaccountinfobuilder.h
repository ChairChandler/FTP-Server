#ifndef FAKEACCOUNTINFOBUILDER_H
#define FAKEACCOUNTINFOBUILDER_H

#include "fakeit.hpp"
#include "accountinfo.h"
using namespace fakeit;

struct FakeAccountInfoBuilder: public AccountInfoBuilder {
        static inline Mock<AccountInfoBuilder> *builder;

    public:
        virtual int buildDataChannelSocket() const override {
            return builder->get().buildDataChannelSocket();
        }
        virtual Transmission* buildTransmission() const override {
            return builder->get().buildTransmission();
        }
        virtual Mode* buildMode() const override {
            return builder->get().buildMode();
        }
        virtual Structure* buildStructure() const override {
            return builder->get().buildStructure();
        }
        virtual FTPfileSystemImpl* buildFileSystem(QString name) const override {
            return builder->get().buildFileSystem(name);
        }
        virtual ~FakeAccountInfoBuilder() override;
        static void setMock(Mock<AccountInfoBuilder> &mock) {
            builder = &mock;
        }

        virtual AccountInfoBuilder* doClone() const override {
            return new FakeAccountInfoBuilder(*this);
        }
};

#endif // FAKEACCOUNTINFOBUILDER_H
