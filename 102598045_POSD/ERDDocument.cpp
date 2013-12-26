#include "ERDDocument.h"
#include "ReorderComponentsUtil.h"
#include "SaveComponentVisitor.h"
#include "ApplicationSetting.h"

ERDDocument::ERDDocument(string fileName,HashMap<string,Component*> componentMap) : Document(fileName,ApplicationSetting::ERDFileExtension),componentMap(componentMap){
}

void ERDDocument::doSaveFile(){
    HashMap<string,string> orderedIDsMap = ReorderComponentsUtil::getReorderedComponentIDMap(this->componentMap);
    SaveComponentVisitor saveComponentVisitor = SaveComponentVisitor(orderedIDsMap);
    //accept all
    for each(Component* component in this->componentMap)
        component->accept(&saveComponentVisitor);
    //save erd file
    for each(string info in saveComponentVisitor.getResult())
        this->writeLine(info);
    //save pos file
    Document posDoc(this->fileName,ApplicationSetting::ERDPositionFileExtension);
    for each(string position in saveComponentVisitor.getPositionInfoVector())
        posDoc.writeLine(position);
    posDoc.saveFile();
}