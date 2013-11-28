#include "CommandManagerTest.h"
#include "AddNodeCommand.h"
#include "ConnectNodeCommand.h"
#include "DeleteComponentCommand.h"
#include "ComponentType.h"
#include "EmptyCollectionException.h"
#include "ComponentFactory.h"

void CommandManagerTest::SetUp(){
    this->commandManager = &this->erModel.commandManager;

    ComponentFactory componentFactory;
    this->entityEngineer = static_cast<Node*>(componentFactory.createComponent(ComponentType::TypeEntity));
    this->entityPC = static_cast<Node*>(componentFactory.createComponent(ComponentType::TypeEntity));
    this->attributeName = static_cast<Node*>(componentFactory.createComponent(ComponentType::TypeAttribute));
    this->relationShipHas = static_cast<Node*>(componentFactory.createComponent(ComponentType::TypeRelationShip));
    this->connectorEngineerName = static_cast<Connector*>(componentFactory.createComponent(ComponentType::TypeConnector));
    this->connectorHasEngineer = static_cast<Connector*>(componentFactory.createComponent(ComponentType::TypeConnector));
    this->connectorHasPC = static_cast<Connector*>(componentFactory.createComponent(ComponentType::TypeConnector));

    ASSERT_EQ(0,this->erModel.componentMap.size());
}

void CommandManagerTest::TearDown(){
}

void CommandManagerTest::executeCommand(){
    ASSERT_THROW(this->commandManager->redo(),Exception);
    ASSERT_THROW(this->commandManager->undo(),Exception);

    this->commandManager->execute(new AddNodeCommand(&this->erModel,this->entityEngineer));
    ASSERT_EQ(1,this->erModel.componentMap.size());
    ASSERT_EQ(this->entityEngineer,this->erModel.componentMap.get(this->entityEngineer->getID()));

    this->commandManager->undo();
    ASSERT_EQ(0,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(1,this->erModel.componentMap.size());

    this->commandManager->execute(new AddNodeCommand(&this->erModel,this->attributeName));
    ASSERT_EQ(2,this->erModel.componentMap.size());
    ASSERT_EQ(this->attributeName,this->erModel.componentMap.get(this->attributeName->getID()));

    this->commandManager->undo();
    ASSERT_EQ(1,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(2,this->erModel.componentMap.size());

    this->commandManager->execute(new AddNodeCommand(&this->erModel,this->relationShipHas));
    ASSERT_EQ(3,this->erModel.componentMap.size());
    ASSERT_EQ(this->relationShipHas,this->erModel.componentMap.get(this->relationShipHas->getID()));

    this->commandManager->undo();
    ASSERT_EQ(2,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(3,this->erModel.componentMap.size());
    ASSERT_THROW(this->commandManager->redo(),Exception);
}

TEST_F(CommandManagerTest,testCommandManager){
    this->executeCommand();

    this->commandManager->undo();
    this->commandManager->undo();
    this->commandManager->undo();
    ASSERT_THROW(this->commandManager->undo(),Exception);

    this->commandManager->redo();
    this->commandManager->redo();
    this->commandManager->redo();
    ASSERT_THROW(this->commandManager->redo(),Exception);

    this->commandManager->execute(new ConnectNodeCommand(&this->erModel,this->entityEngineer,this->attributeName,this->connectorEngineerName));
    ASSERT_EQ(4,this->erModel.componentMap.size());
    ASSERT_EQ(this->connectorEngineerName,this->erModel.componentMap.get(this->connectorEngineerName->getID()));

    this->commandManager->undo();
    ASSERT_EQ(3,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(4,this->erModel.componentMap.size());

    this->commandManager->execute(new ConnectNodeCommand(&this->erModel,this->entityEngineer,this->relationShipHas,this->connectorHasEngineer));
    ASSERT_EQ(5,this->erModel.componentMap.size());
    ASSERT_EQ(this->connectorHasEngineer,this->erModel.componentMap.get(this->connectorHasEngineer->getID()));

    this->commandManager->undo();
    ASSERT_EQ(4,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(5,this->erModel.componentMap.size());

    this->commandManager->execute(new AddNodeCommand(&this->erModel,this->entityPC));
    ASSERT_EQ(6,this->erModel.componentMap.size());
    ASSERT_EQ(this->entityPC,this->erModel.componentMap.get(this->entityPC->getID()));

    this->commandManager->undo();
    ASSERT_EQ(5,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(6,this->erModel.componentMap.size());

    this->commandManager->execute(new ConnectNodeCommand(&this->erModel,this->entityPC,this->relationShipHas,this->connectorHasPC));
    ASSERT_EQ(7,this->erModel.componentMap.size());
    ASSERT_EQ(this->connectorHasPC,this->erModel.componentMap.get(this->connectorHasPC->getID()));

    this->commandManager->undo();
    ASSERT_EQ(6,this->erModel.componentMap.size());
    this->commandManager->redo();
    ASSERT_EQ(7,this->erModel.componentMap.size());
    //test delete component - connectorEngineer&Name
    this->commandManager->execute(new DeleteComponentCommand(&this->erModel,this->connectorEngineerName));
    ASSERT_EQ(6,this->erModel.componentMap.size());
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(false,this->attributeName->hasConnectedTo(this->entityEngineer));

    this->commandManager->undo();
    ASSERT_EQ(7,this->erModel.componentMap.size());
    ASSERT_EQ(true,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(true,this->attributeName->hasConnectedTo(this->entityEngineer));
    //test delete component - attributeName
    this->commandManager->execute(new DeleteComponentCommand(&this->erModel,this->attributeName));
    ASSERT_EQ(5,this->erModel.componentMap.size());
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(false,this->attributeName->hasConnectedTo(this->entityEngineer));

    this->commandManager->undo();
    ASSERT_EQ(7,this->erModel.componentMap.size());
    ASSERT_EQ(true,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(true,this->attributeName->hasConnectedTo(this->entityEngineer));
    //test delete component - relationShipHas
    this->commandManager->execute(new DeleteComponentCommand(&this->erModel,this->relationShipHas));
    ASSERT_EQ(4,this->erModel.componentMap.size());
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->relationShipHas));
    ASSERT_EQ(false,this->relationShipHas->hasConnectedTo(this->entityEngineer));

    this->commandManager->undo();
    ASSERT_EQ(7,this->erModel.componentMap.size());
    ASSERT_EQ(true,this->entityEngineer->hasConnectedTo(this->relationShipHas));
    ASSERT_EQ(true,this->relationShipHas->hasConnectedTo(this->entityEngineer));
    //test delete component - entityEngineer
    this->commandManager->execute(new DeleteComponentCommand(&this->erModel,this->entityEngineer));
    ASSERT_EQ(4,this->erModel.componentMap.size());
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->relationShipHas));
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(false,this->relationShipHas->hasConnectedTo(this->entityEngineer));
    ASSERT_EQ(false,this->attributeName->hasConnectedTo(this->entityEngineer));

    this->commandManager->undo();
    ASSERT_EQ(7,this->erModel.componentMap.size());
    ASSERT_EQ(true,this->entityEngineer->hasConnectedTo(this->relationShipHas));
    ASSERT_EQ(true,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(true,this->relationShipHas->hasConnectedTo(this->entityEngineer));
    ASSERT_EQ(true,this->attributeName->hasConnectedTo(this->entityEngineer));

    this->commandManager->redo();
    ASSERT_EQ(4,this->erModel.componentMap.size());
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->relationShipHas));
    ASSERT_EQ(false,this->entityEngineer->hasConnectedTo(this->attributeName));
    ASSERT_EQ(false,this->relationShipHas->hasConnectedTo(this->entityEngineer));
    ASSERT_EQ(false,this->attributeName->hasConnectedTo(this->entityEngineer));
}

TEST_F(CommandManagerTest,testRedoUndo){
    this->executeCommand();
    this->commandManager->undo();
    ASSERT_EQ(2,this->erModel.componentMap.size());
    this->commandManager->undo();
    ASSERT_EQ(1,this->erModel.componentMap.size());
    this->commandManager->undo();
    ASSERT_EQ(0,this->erModel.componentMap.size());

    this->commandManager->execute(new AddNodeCommand(&this->erModel,this->entityPC));
    ASSERT_EQ(1,this->erModel.componentMap.size());
    ASSERT_EQ(this->entityPC,this->erModel.componentMap.get(this->entityPC->getID()));

    this->commandManager->execute(new DeleteComponentCommand(&this->erModel,this->entityPC));
    ASSERT_EQ(0,this->erModel.componentMap.size());
}

TEST_F(CommandManagerTest,testPopAllStack){
    ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
    ASSERT_EQ(0,this->commandManager->undoCommandsStack.size());
    this->commandManager->redoCommandsStack.push(new AddNodeCommand(&this->erModel,this->attributeName));
    this->commandManager->redoCommandsStack.push(new DeleteComponentCommand(&this->erModel,this->attributeName));
    this->commandManager->redoCommandsStack.push(new AddNodeCommand(&this->erModel,this->entityEngineer));
    this->commandManager->popAllStack();
    ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
    ASSERT_EQ(0,this->commandManager->undoCommandsStack.size());

    this->commandManager->undoCommandsStack.push(new AddNodeCommand(&this->erModel,this->relationShipHas));
    this->commandManager->undoCommandsStack.push(new AddNodeCommand(&this->erModel,this->entityPC));
    this->commandManager->popAllStack();
    ASSERT_EQ(0,this->commandManager->redoCommandsStack.size());
    ASSERT_EQ(0,this->commandManager->undoCommandsStack.size());
}