#pragma once

#include "FileProcess.h"
#include <gtest/gtest.h>

class FileProcessTest : public testing::Test{
protected:
    virtual void SetUp();
    virtual void TearDown();
};