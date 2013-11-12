#include "Size.h"

#include "WidgetDefaultSetting.h"

Size::Size(double width,double height) : width(width),height(height){
}

double Size::getWidth(){
    return this->width;
}

double Size::getHeight(){
    return this->height;
}

bool Size::operator==(const Size& sizeToCompare) const{
    if(this->width == sizeToCompare.width && this->height == sizeToCompare.height)
        return true;
    return false;
}

Size& Size::operator+=(const Size& sizeToAdd){
    this->width += sizeToAdd.width;
    this->height += sizeToAdd.height;
    return *this;
}

Size Size::DefaultSize(){
    return Size(WidgetDefaultSetting::Width,WidgetDefaultSetting::Height);
}