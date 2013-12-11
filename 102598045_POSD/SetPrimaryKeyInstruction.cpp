#include "SetPrimaryKeyInstruction.h"
#include "Entity.h"
#include "StringUtil.h"
#include "CharSymbol.h"
#include "Entity.h"
#include "ControllerEvent.h"

void SetPrimaryKeyInstruction::execute(TextPresentation* textPresentation,TextUIPresenter* textUIPresenter){
    textUIPresenter->displayEntities();
    cout<<"Enter the ID of the entity: "<<endl;
    Entity* entity = textPresentation->findEntity();
    textUIPresenter->displayEntityAttributes(entity);
    cout<<"Enter the IDs of the attributes (use a comma to separate two attributes):"<<endl;
    vector<string> attributeIDVector = this->setEntityAttributesPrimaryKey(entity,textPresentation);
    //display Set Primary Key Result
    cout<<"The entity '"+entity->getID()+"' has the primary key ("+StringUtil::appendWithComma(attributeIDVector)+")."<<endl;
    textPresentation->sync(ControllerEvent::SetPrimaryKey);
}

vector<string> SetPrimaryKeyInstruction::setEntityAttributesPrimaryKey(Entity* entity,TextPresentation* textPresentation){
    vector<string> attributeIDVector;
    while(true){
        try{
            string input = textPresentation->getInput();
            attributeIDVector = StringUtil::split(input,CharSymbol::Comma);
            for each(string id in attributeIDVector){
                textPresentation->setPrimaryKey(id);
            }
            break;
        }
        catch(Exception& exception){
            cout<<exception.what()<<endl;
        }
    }
    return  attributeIDVector;
}