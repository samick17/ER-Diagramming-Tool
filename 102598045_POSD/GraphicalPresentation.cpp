#include "GraphicalPresentation.h"
#include <iostream>
#include <iomanip>
#include <QFileDialog>
#include "StringSymbol.h"
#include "ComponentType.h"
#include "GraphicalUI.h"
#include "ActionData.h"
#include "ApplicationSetting.h"

GraphicalPresentation::GraphicalPresentation(Presentation* presentation) : presentation(presentation){
}

GraphicalPresentation::~GraphicalPresentation(){
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