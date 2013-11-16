#include "QActionData.h"

QActionData::QActionData(string actionText,string iconPath,string keySequence) : actionText(actionText),iconPath(iconPath),keySequence(keySequence){
}

QActionData::~QActionData(){
}

string QActionData::getActionText(){
    return this->actionText;
}

string QActionData::getIconPath(){
    return this->iconPath;
}

string QActionData::getKeySequence(){
    return this->keySequence;
}