#ifndef FAKEACCOUNTDATABASEFACTORY_H
#define FAKEACCOUNTDATABASEFACTORY_H

#include "fakeit.hpp"
#include "accountdatabase.h"
using namespace fakeit;

struct FakeAccountDatabaseSingletonFactory: public AccountDatabaseSingletonFactory {
    static inline Mock<AccountDatabase> *database;

    static void setMock(Mock<AccountDatabase> &mock) {
        database = &mock;
    }

    virtual AccountDatabase& getInstance() override {
        return database->get();
    }

    virtual AccountDatabaseSingletonFactory* doClone() const override {
        return new FakeAccountDatabaseSingletonFactory(*this);
    }

    virtual ~FakeAccountDatabaseSingletonFactory() override;
};

#endif // FAKEACCOUNTDATABASEFACTORY_H
