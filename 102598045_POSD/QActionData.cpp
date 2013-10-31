#include "QActionData.h"

QActionData::QActionData(string actionText,string iconPath,string keySequence) : actionText(actionText),iconPath(iconPath){
    this->keySequence = QKeySequence(keySequence.c_str());
}

QActionData::~QActionData(){
}

string QActionData::getActionText(){
    return this->actionText;
}

string QActionData::getIconPath(){
    return this->iconPath;
}

QKeySequence QActionData::getKeySequence(){
    return this->keySequence;
}