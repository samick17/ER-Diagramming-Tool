#pragma once

class ERModel;

class ClipBoardState{
public:
    ClipBoardState(ERModel* erModel);
    virtual ~ClipBoardState();

    virtual bool canPaste() = 0;
    virtual void paste() = 0;
protected:
    ERModel* erModel;
};