#include "QActionData.h"
#include "ActionData.h"

QActionData::QActionData(unsigned int actionIndex) : actionIndex(actionIndex){
    this->actionText = ActionData::ActionName[actionIndex];
    this->iconPath = ActionData::ActionIconPath[actionIndex];
    this->keySequence = ActionData::ActionShortCutKey[actionIndex];
}

QActionData::~QActionData(){
}

unsigned int QActionData::getActionIndex(){
    return this->actionIndex;
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