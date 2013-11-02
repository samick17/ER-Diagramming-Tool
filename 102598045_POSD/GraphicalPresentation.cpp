#include "GraphicalPresentation.h"
#include <QFileDialog>
#include "ActionData.h"
#include "ApplicationSetting.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
}

GraphicalPresentation::~GraphicalPresentation(){
    this->deleteAndClearAllComponentWidget();
}

HashMap<string,ComponentWidget*> GraphicalPresentation::getAllComponentWidgets(){
    this->deleteAndClearAllComponentWidget();
    this->updateComponentWidgetMap();
    //calculate widget position
    return this->componentWidgetMap;
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

void GraphicalPresentation::deleteAndClearAllComponentWidget(){
    for each(ComponentWidget* componentWidget in this->componentWidgetMap)
        delete componentWidget;
    this->componentWidgetMap.clear();
}

void GraphicalPresentation::updateComponentWidgetMap(){
    this->deleteAndClearAllComponentWidget();
    WidgetFactory widgetFactory;
    for each(Component* component in this->presentation->getAllComponents()){
        this->componentWidgetMap.put(component->getID(),widgetFactory.createComponentWidget(component->getType()));
    }
}