#pragma once

#include <gtest/gtest.h>
#include "ERModel.h"
#include "TextPresentation.h"

class DeleteComponentCommandTest : public testing::Test{
protected:
    ERModel erModel;
	Presentation* presentation;
    TextPresentation* textPresentation;
    virtual void SetUp();
    virtual void TearDown();
};