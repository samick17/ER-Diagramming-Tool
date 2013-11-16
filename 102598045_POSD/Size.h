#pragma once

#include "WidgetDefaultSetting.h"
#include <gtest/gtest_prod.h> 

struct Size{
    friend class SizeTest;
public:
    Size(double width = WidgetDefaultSetting::Width,double height = WidgetDefaultSetting::Height);

    double getWidth();
    double getHalfWidth();
    double getHeight();
    double getHalfHeight();

    bool operator==(const Size& sizeToCompare) const;
    Size& operator+=(const Size& sizeToAdd);

    static Size DefaultSize();
private:
    double width;
    double height;
};