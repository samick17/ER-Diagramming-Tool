#include "TextUIProcess.h"
#include "ERModel.h"
#include "Presentation.h"
#include "CommandManager.h"
#include "TextUI.h"

TextUIProcess::TextUIProcess(){
}

TextUIProcess::~TextUIProcess(){
}

void TextUIProcess::run(){
	ERModel erModel;	
	Presentation presentation(&erModel);
	CommandManager commandManager(&presentation);
	presentation.setCommandManager(&commandManager);
	TextUI textUI(&presentation);
	
	while(textUI.isAlive()){
		textUI.displayMenu();
		textUI.processCommand();
	}
}