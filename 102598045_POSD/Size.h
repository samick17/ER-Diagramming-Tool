#pragma once

struct Size{
public:
    Size(double width,double height);

    double getWidth();
    double getHeight();

    bool operator==(const Size& sizeToCompare) const;
    Size& operator+=(const Size& sizeToAdd);

    static Size DefaultSize();
private:
    double width;
    double height;
};