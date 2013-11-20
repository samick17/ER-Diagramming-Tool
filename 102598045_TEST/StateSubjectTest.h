#pragma once

#include "StateSubject.h"
#include <gtest/gtest.h>

class StateSubjectTest : public testing::Test{
protected:
    StateSubject stateSubject;
    virtual void SetUp();
    virtual void TearDown();
};