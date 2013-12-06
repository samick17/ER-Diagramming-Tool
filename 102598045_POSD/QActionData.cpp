#include "QActionData.h"
#include "ActionData.h"

QActionData::QActionData(unsigned int actionIndex) : actionIndex(actionIndex){
    this->actionText = ActionData::ActionName[actionIndex];
    this->iconPath = ActionData::ActionIconPath[actionIndex];
    this->keySequence = ActionData::ActionShortCutKey[actionIndex];
    this->initialToolTip(this->actionText,this->keySequence);
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

string QActionData::getToolTip(){
    return this->toolTip;
}

string QActionData::initialToolTip(string actionText,string keySequence){
    string toolTip = actionText;
    if(keySequence != StringSymbol::Empty)
        toolTip += "("+keySequence+")";
    toolTip;
    return toolTip;
}