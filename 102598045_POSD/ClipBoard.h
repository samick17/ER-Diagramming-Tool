#pragma once

#include "HashMap.h"
#include <gtest/gtest_prod.h>

class Component;

class ClipBoard{
    friend class CutComponentsCommandTest;
    FRIEND_TEST(CutComponentsCommandTest,testExecuteCutConnectorWithOneNode);
public:
    ClipBoard();
    ~ClipBoard();

    void setData(HashMap<string,Component*> componentMap);
    HashMap<string,Component*> getData();
    void clearData();
private:
    HashMap<string,Component*> clonedAllComponents(HashMap<string,Component*> componentMap);
    HashMap<string,Component*> componentMap;
};