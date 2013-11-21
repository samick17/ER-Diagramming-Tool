#include "AddDrawableToolBar.h"
#include "ToolBarWidget.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "StateID.h"
#include "GraphicalPresentation.h"
#include "StateSubject.h"

AddDrawableToolBar::AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    this->currentFocusedWidget = NULL;
    unsigned int actionIndex = ActionData::PointerState;
    for(int index = StateID::PointerState; index <= StateID::SetPrimaryKeyState; index++){
        ToolBarWidget* toolBarWidget = new ToolBarWidget(this,actionMap,actionIndex);
        this->toolBarWidgetMap.put(index,toolBarWidget);
        this->addWidget(toolBarWidget);
        actionIndex++;
    }
    //initial state subject
    GraphicalPresentation* graphicalPresentation = graphicalUI->getGraphicalPresentation();
    this->stateSubject = graphicalPresentation->getStateSubject();
    this->stateSubject->registerObserver(this);
}

AddDrawableToolBar::~AddDrawableToolBar(){
    this->stateSubject->unregisterObserver(this);
}

void AddDrawableToolBar::selectToolButton(int stateID){
    if(this->currentFocusedWidget)
        this->currentFocusedWidget->setChecked(false);
    ToolBarWidget* nextSelectToolButton = this->toolBarWidgetMap.get(stateID);
    nextSelectToolButton->setChecked(true);
    this->currentFocusedWidget = nextSelectToolButton;
}

void AddDrawableToolBar::notify(ISubject* subject){
    //update widget according to StateSubject
    State* state = this->stateSubject->getState();
    this->selectToolButton(state->getStateID());
}