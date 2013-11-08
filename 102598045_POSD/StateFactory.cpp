#include "StateFactory.h"
#include "StateID.h"
#include "PointerState.h"
#include "ConnectState.h"
#include "AddNodeState.h"

StateFactory::StateFactory(){
    this->newStateMap.put(StateID::PointerState,newState<PointerState>);
    this->newStateMap.put(StateID::ConnectState,newState<ConnectState>);
    this->newStateMap.put(StateID::AttributeState,newState<AddNodeState>);
    this->newStateMap.put(StateID::EntityState,newState<AddNodeState>);
    this->newStateMap.put(StateID::RelationShipState,newState<AddNodeState>);
}

StateFactory::~StateFactory(){
}

State* StateFactory::createState(int stateID,GraphicalPresentation* graphicalPresentation){
    NewStateFunction newStateFunction = this->findNewStateFunction(stateID);
    return newStateFunction(stateID,graphicalPresentation);
}

NewStateFunction StateFactory::findNewStateFunction(int stateID){
    return this->newStateMap.get(stateID);
}