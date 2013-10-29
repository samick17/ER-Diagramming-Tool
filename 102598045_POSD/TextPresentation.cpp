#include "TextPresentation.h"
#include <iostream>
#include <iomanip>
#include "Node.h"
#include "Entity.h"
#include "Connector.h"
#include "ComponentUtil.h"
#include "ERModelUtil.h"
#include "StringUtil.h"
#include "CommandMenu.h"
#include "NullPointerException.h"
#include "EmptyCollectionException.h"
#include "InvalidNodeTypeException.h"
#include "StringSymbol.h"
#include "CharSymbol.h"
#include "ComponentType.h"
#include "ERModel.h"
#include "TextUI.h"
#include "InputFileParser.h"
#include "OutputFileParser.h"

TextPresentation::TextPresentation(ERModel* erModel) : erModel(erModel){
}

TextPresentation::~TextPresentation(){
}

ERModel* TextPresentation::getERModel(){
    return this->erModel;
}

void TextPresentation::openFile(){
    cout<<"Please input the file name: "<<endl;
    string filePath = this->textUI->getInput();
    InputFileParser inputFileParser;
    inputFileParser.parseFileToModel(filePath,erModel);
    this->displayDiagram();
}

void TextPresentation::saveFile(){
    cout<<"Please input the file name: "<<endl;
	string filePath = this->textUI->getInput();
    OutputFileParser outputFileParser = OutputFileParser(this->erModel->getAllComponents());
    outputFileParser.parseModelToFile(filePath);
}
//if alive == false,program will close
void TextPresentation::close(){
    this->alive = false;
    cout<<"GooBye!"<<endl;
    exit(0);
}

void TextPresentation::displayDiagram(){
    //display current diagram
    this->textUI->displayDiagram();
}

void TextPresentation::displayTable(){
    HashMap<string,Table*> tableMap = erModel->getAllTables();
    if(tableMap.empty())
        throw EmptyCollectionException("Tables");
    this->textUI->displayTable(tableMap);
}

void TextPresentation::displayComponents(){
    HashMap<string,Component*> componentMap = erModel->getAllComponents();
    if(componentMap.empty())
        throw EmptyCollectionException(ComponentType::TypeComponent);
    this->textUI->displayComponents(componentMap);
}

void TextPresentation::displayConnections(){
    HashMap<string,Connector*> connectorMap = erModel->getAllConnectors();
    if(connectorMap.empty())
        throw EmptyCollectionException(ComponentType::TypeConnectorName);
    this->textUI->displayConnections(connectorMap);
}

void TextPresentation::displayEntities(){
    HashMap<string,Entity*> entityMap = erModel->getAllEntities();
    if(entityMap.empty())
        throw EmptyCollectionException(ComponentType::TypeEntityName);
    this->textUI->displayEntities(ComponentUtil::toComponentHashMap<Entity>(entityMap));
}

void TextPresentation::displayEntityAttributes(Entity* entity){
    HashMap<string,Attribute*> attributeMap = entity->getConnectedAttributes();
    if(attributeMap.empty())
        throw EmptyCollectionException(ComponentType::TypeAttributeName);
    this->textUI->displayEntityAttributes(entity,ComponentUtil::toComponentHashMap<Attribute>(attributeMap));
}

Component* TextPresentation::findComponent(){
    //get All Components too check there has components to find
    this->erModel->getAllComponents();

    string input;
    Component* find = NULL;
    while(find == NULL){
        try{
            input = this->textUI->getInput();
            find = this->erModel->getComponentByID(input);
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    return find;
}

Entity* TextPresentation::findEntity(){
	Component* find = this->findComponent();
    while(typeid(*find).name() != typeid(Entity).name()){
        cout<<"The node '"+find->getID()+"' is not an entity. Please enter a valid one again."<<endl;
        find = this->findComponent();
    }
    return static_cast<Entity*>(find);
}

void TextPresentation::processCommand(string commandKey){
    Command* command = NULL;
    try{
        CommandMenu commandMenu;
        CommandData* commandData = commandMenu.getCommandDataByKey(commandKey);
        //get new Command Function From Command Data
        CommandInstruction commandInstruction = commandData->getCommandInstruction();
        (this->*commandInstruction)();
    }
    catch(NullPointerException){
        this->textUI->alertException("wrong command,please input correct command.");
    }
    catch(Exception& exception){
        this->textUI->alertException(exception.getMessage());
        delete command;
    }
}

void TextPresentation::addNode(){
    cout<<"What kind of node do you want to add?\n[A]Attribute [E]Entity [R]Relation"<<endl;
    Node* node = NULL;
    while(node == NULL){
        try{
            string input = this->textUI->getInput();
            if(input == ComponentType::TypeConnector)
                throw InvalidNodeTypeException();
            node = this->erModel->addNode(input);
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    this->setNodeName(node);
    this->displayComponents();
}

void TextPresentation::deleteComponent(){
   //find node to be connect
    cout<<"Please enter the component ID"<<endl;
    Component* componentToDelete = this->findComponent();
    this->erModel->deleteComponent(componentToDelete);
    cout<<"The component '"+componentToDelete->getID()+"' has been deleted. "<<endl;
}

void TextPresentation::connectTwoNodes(){
    HashMap<string,Component*> componentMap = this->erModel->getAllComponents();
    if(componentMap.empty())
        throw EmptyCollectionException("Nodes");
    cout<<"Please enter the first node ID"<<endl;
    Component* firstNode = this->findComponent();
    cout<<"Please enter the second node ID"<<endl;
    Component* secondNode = this->findComponent();

    int result = this->erModel->addConnection(firstNode,secondNode);
    if(result == NodeConnectionType::ConnectEntityAndRelation)
        this->setCardinality(firstNode,secondNode);
    else if(result == NodeConnectionType::ValidConnect)
        cout<<"The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"' successfully!"<<endl;
    this->displayConnections();
}

void TextPresentation::redo(){
    this->erModel->redo();
    cout<<"Redo succeed."<<endl;
    this->displayComponents();
    this->displayConnections();
}

void TextPresentation::undo(){
    this->erModel->undo();
    cout<<"Undo succeed."<<endl;
    this->displayComponents();
    this->displayConnections();
}

void TextPresentation::setCardinality(Component* firstNode,Component* secondNode){
    HashMap<string,string> cardinalityPairMap;
    cardinalityPairMap.put("0",RelationType::OneToOne);
    cout<<"Enter the type of the cardinality: "<<endl;
    cout<<"[0]1 [1]N"<<endl;
    cout<<"The node '"+firstNode->getID()+"' has been connected to the node '"+secondNode->getID()+"'."<<endl;    
    string input = this->textUI->getInput();

    while(!cardinalityPairMap.containsKey(input)){
        cout<<"the cardinality you entered doesn't exist. Please entered a valid one again"<<endl;        
        input = this->textUI->getInput();
    }

    Connector* connection = erModel->getNodesConnector(firstNode,secondNode);
    string relationName = cardinalityPairMap.get(input);
    connection->setName(relationName);
    cout<<"Its cardinality of the relationship is '"+relationName+"'."<<endl;
}

void TextPresentation::setNodeName(Node* nodeToSetName){
    cout<<"Enter the name of this node:"<<endl;
    string input = this->textUI->getInput();
    //node name out of range
    while(input.size() >= TABLE_WIDTH){
        cout<<"The name you entered is too long,please enter a concise one again."<<endl;
        input = this->textUI->getInput();
    }

    nodeToSetName->setName(input);
    cout<<"A node ["+nodeToSetName->getClassName()+"] has been added. ID: "+nodeToSetName->getID()+",Name: "+nodeToSetName->getName()<<endl;
}

void TextPresentation::setPrimaryKey(){
    this->displayEntities();
    cout<<"Enter the ID of the entity: "<<endl;
    Entity* entity = static_cast<Entity*>(this->findEntity());
    this->displayEntityAttributes(entity);
    cout<<"Enter the IDs of the attributes (use a comma to separate two attributes):"<<endl;
    vector<string> attributeIDVector = setEntityAttributesPrimaryKey(entity);
    //display Set Primary Key Result
    cout<<"The entity '"+entity->getID()+"' has the primary key ("+StringUtil::appendWithComma(attributeIDVector)+")."<<endl;
}

vector<string> TextPresentation::setEntityAttributesPrimaryKey(Entity* entity){
    vector<string> attributeIDVector;
    while(true){
        try{
            string input = this->textUI->getInput();
            attributeIDVector = StringUtil::split(input,CharSymbol::Comma);
            entity->setPrimaryKey(attributeIDVector);
            break;
        }
        catch(Exception& exception){
            cout<<exception.getMessage()<<endl;
        }
    }
    return  attributeIDVector;
}

void TextPresentation::setTextUI(TextUI* textUI){
    this->textUI = textUI;
}