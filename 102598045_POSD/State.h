#pragma once

#include "Point.h"

class GraphicalPresentation;

class State{
public:
    State(int stateID,GraphicalPresentation* graphicalPresentation);
    virtual ~State();

    virtual void onCreate();
    int getStateID();

    void mousePressEvent(Point position);
    void mouseMoveEvent(Point position);
    void mouseReleaseEvent(Point position);
protected:
    GraphicalPresentation* graphicalPresentation;

    Point getDeltaPosition();
    virtual void doMousePressEvent(Point position) = 0;
    virtual void doMouseMoveEvent(Point position) = 0;
    virtual void doMouseDragEvent(Point position) = 0;
    virtual void doMouseReleaseEvent(Point position) = 0;
private:
    int stateID;
    bool isMousePressed;
    Point currentPosition;
    Point deltaPosition;
};