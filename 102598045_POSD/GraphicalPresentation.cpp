#include "GraphicalPresentation.h"
#include <iostream>
#include <iomanip>
#include <QFileDialog>
#include "StringSymbol.h"
#include "ComponentType.h"
#include "GraphicalUI.h"
#include "ActionData.h"
#include "ApplicationSetting.h"
#include "Attribute.h"
#include "Entity.h"
#include "RelationShip.h"
#include "Connector.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
}

GraphicalPresentation::~GraphicalPresentation(){
}

HashMap<string,Attribute*> GraphicalPresentation::getAllAttributes(){
    return this->presentation->getAllAttributes();
}

HashMap<string,Entity*> GraphicalPresentation::getAllEntities(){
    return this->presentation->getAllEntities();
}

HashMap<string,RelationShip*> GraphicalPresentation::getAllRelationShips(){
    return this->presentation->getAllRelationShips();
}

HashMap<string,Connector*> GraphicalPresentation::getAllConnectors(){
    return this->presentation->getAllConnectors();
}

void GraphicalPresentation::openFile(){
    QFileDialog* openFileDialog = new QFileDialog(NULL, QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    openFileDialog->exec();
    QString filePath = openFileDialog->selectedFiles().first();
    if(!filePath.isEmpty())
        this->presentation->openFile(filePath.toStdString());
    delete openFileDialog;
}

void GraphicalPresentation::saveFile(){
    QFileDialog* saveFileDialog = new QFileDialog(NULL, QString(ActionData::OpenFile.c_str()),QString(ApplicationSetting::FilePath.c_str()),QString(ApplicationSetting::FileExtension.c_str()));
    saveFileDialog->exec();
    QString filePath = saveFileDialog->selectedFiles().first();
    if(!filePath.isEmpty())
        this->presentation->saveFile(filePath.toStdString());
    delete saveFileDialog;
}

void GraphicalPresentation::close(){
    this->presentation->close();
}