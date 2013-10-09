#include <tchar.h>
#include "TextUI.h"
#include "Presentation.h"
#include "CommandManager.h"

int _tmain(int argc,_TCHAR* argv[]){		
	ERModel erModel;	
	Presentation presentation(&erModel);
	CommandManager commandManager(&presentation);
	presentation.setCommandManager(&commandManager);
	TextUI textUI = TextUI(&presentation);
	
	while(textUI.isAlive()){
		textUI.displayMenu();
		textUI.processCommand();
	}

	return 0;
}