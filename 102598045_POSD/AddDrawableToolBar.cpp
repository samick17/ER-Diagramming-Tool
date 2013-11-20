#include "AddDrawableToolBar.h"
#include "ToolBarWidget.h"
#include "ActionData.h"
#include "GraphicalUI.h"
#include "StateID.h"
#include "GraphicalPresentation.h"
#include "StateSubject.h"

AddDrawableToolBar::AddDrawableToolBar(GraphicalUI* graphicalUI,QActionMap* actionMap) : QToolBar(graphicalUI){
    this->currentFocusedWidget = NULL;
    this->toolBarWidgetMap.put(StateID::PointerState,new ToolBarWidget(this,actionMap,ActionData::PointerState));
    this->toolBarWidgetMap.put(StateID::ConnectState,new ToolBarWidget(this,actionMap,ActionData::ConnectState));
    this->toolBarWidgetMap.put(StateID::AddAttributeState,new ToolBarWidget(this,actionMap,ActionData::AttributeState));
    this->toolBarWidgetMap.put(StateID::AddEntityState,new ToolBarWidget(this,actionMap,ActionData::EntityState));
    this->toolBarWidgetMap.put(StateID::AddRelationShipState,new ToolBarWidget(this,actionMap,ActionData::RelationShipState));
    for each(ToolBarWidget* toolBarWidget in toolBarWidgetMap)
        this->addWidget(toolBarWidget);
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