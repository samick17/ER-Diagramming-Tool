#include "MyThread.h"
#include "ERModel.h"
#include "Presentation.h"
#include "CommandManager.h"
#include "TextUI.h"

MyThread::MyThread(){
}

MyThread::~MyThread(){
}

void MyThread::run(){
	ERModel erModel;	
	Presentation presentation(&erModel);
	CommandManager commandManager(&presentation);
	presentation.setCommandManager(&commandManager);
	TextUI textUI = TextUI(&presentation);
	
	while(textUI.isAlive()){
		textUI.displayMenu();
		textUI.processCommand();
	}
}