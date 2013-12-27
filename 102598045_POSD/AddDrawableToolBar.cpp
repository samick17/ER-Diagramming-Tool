#include "AddDrawableToolBar.h"
#include "ToolBarWidget.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "StateID.h"
#include "GraphicalPresentation.h"
#include "StateSubject.h"

AddDrawableToolBar::AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    this->currentFocusedWidget = NULL;
    //initial state tool bar widget
    unsigned int actionIndex = ActionData::PointerState;
    for(int index = StateID::PointerState; index <= StateID::SetPrimaryKeyState; index++){
        ToolBarWidget* toolBarWidget = new ToolBarWidget(this,actionMap,actionIndex);
        this->toolBarWidgetMap.put(index,toolBarWidget);
        this->addWidget(toolBarWidget);
        actionIndex++;
    }
    //initial state subject
    this->graphicalPresentation = graphicalUI->getGraphicalPresentation();
    this->graphicalPresentation->registerObserverToStateSubject(this);
}

AddDrawableToolBar::~AddDrawableToolBar(){
    this->graphicalPresentation->unregisterObserverToStateSubject(this);
}

void AddDrawableToolBar::selectToolButton(int stateID){
    if(this->currentFocusedWidget)
        this->currentFocusedWidget->setChecked(false);
    ToolBarWidget* nextSelectToolButton = this->toolBarWidgetMap.get(stateID);
    nextSelectToolButton->setChecked(true);
    this->currentFocusedWidget = nextSelectToolButton;
}

void AddDrawableToolBar::notify(Subject* subject){
    //update widget according to StateSubject
    this->selectToolButton(this->graphicalPresentation->getCurrentStateID());
}