#pragma once

#include "StateSubject.h"
#include <gtest/gtest.h>

class StateSubjectTest : public testing::Test{
protected:
    virtual void SetUp();
    virtual void TearDown();
};