#pragma once

#include "Point.h"
#include <gtest/gtest_prod.h> 

class GraphicalPresentation;

class State{
    friend class StateTest;
    FRIEND_TEST(StateTest,testMousePressEvent);
    FRIEND_TEST(StateTest,testMouseMoveEvent);
    FRIEND_TEST(StateTest,testMouseDragEvent);
    FRIEND_TEST(StateTest,testMouseReleaseEvent);
    friend class ConnectStateTest;
    FRIEND_TEST(ConnectStateTest,testDoMouseDragEvent);
    friend class PointerStateTest;
    FRIEND_TEST(PointerStateTest,testDoMouseDragEvent);
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);
    virtual ~State();

    virtual void onCreate();
    int getStateID();

    void mousePressEvent(Point position);
    void mouseMoveEvent(Point position);
    void mouseReleaseEvent(Point position);
protected:
    Point getDeltaPosition();
    virtual void doMousePressEvent(Point position) = 0;
    virtual void doMouseMoveEvent(Point position) = 0;
    virtual void doMouseDragEvent(Point position) = 0;
    virtual void doMouseReleaseEvent(Point position) = 0;
    GraphicalPresentation* graphicalPresentation;
private:
    int stateID;
    bool isMousePressed;
    Point currentPosition;
    Point deltaPosition;
};