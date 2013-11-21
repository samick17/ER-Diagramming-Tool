#include "StateFactory.h"
#include "StateID.h"
#include "PointerState.h"
#include "ConnectState.h"
#include "AddNodeState.h"
#include "SetPrimaryKeyState.h"

StateFactory::StateFactory(){
    this->newStateMap.put(StateID::PointerState,newState<PointerState>);
    this->newStateMap.put(StateID::ConnectState,newState<ConnectState>);
    this->newStateMap.put(StateID::AddAttributeState,newState<AddNodeState>);
    this->newStateMap.put(StateID::AddEntityState,newState<AddNodeState>);
    this->newStateMap.put(StateID::AddRelationShipState,newState<AddNodeState>);
    this->newStateMap.put(StateID::SetPrimaryKeyState,newState<SetPrimaryKeyState>);
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