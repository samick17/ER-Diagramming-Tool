#pragma once

#include "WidgetDefaultSetting.h"

struct Size{
public:
	Size(double width = WidgetDefaultSetting::Width,double height = WidgetDefaultSetting::Height);

    double getWidth();
    double getHeight();

    bool operator==(const Size& sizeToCompare) const;
    Size& operator+=(const Size& sizeToAdd);

    static Size DefaultSize();
private:
    double width;
    double height;
};