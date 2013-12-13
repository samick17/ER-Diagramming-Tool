#pragma once

#include "Command.h"
#include "HashMap.h"
#include "Component.h"
#include <gtest/gtest_prod.h> 

class MoveComponentsCommand : public Command{
public:
    MoveComponentsCommand(HashMap<string,Component*> selectedComponentMap,Point mousePressPosition,Point mouseReleasePosition);
    ~MoveComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
private:
    HashMap<string,Component*> selectedComponentMap;
    Point mousePressPosition,mouseReleasePosition,deltaPosition;
};