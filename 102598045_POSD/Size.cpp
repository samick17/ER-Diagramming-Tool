#include "Size.h"
#include "WidgetDefaultSetting.h"
#include "Number.h"

Size::Size(double width,double height) : width(width),height(height){
}

double Size::getWidth(){
    return this->width;
}

double Size::getHalfWidth(){
    return this->width/Number::Two;
}

double Size::getHeight(){
    return this->height;
}

double Size::getHalfHeight(){
    return this->height/Number::Two;
}

bool Size::operator==(const Size& sizeToCompare) const{
    if(this->width == sizeToCompare.width && this->height == sizeToCompare.height)
        return true;
    return false;
}