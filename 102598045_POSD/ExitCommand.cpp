#include "ExitCommand.h"

ExitCommand::ExitCommand(TextPresentation* textPresentation) : Command(textPresentation){
}

ExitCommand::~ExitCommand(){
}

void ExitCommand::execute(){
    this->textPresentation->close();
}