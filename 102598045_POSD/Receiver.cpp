#include "Receiver.h"

Receiver::Receiver(int key,Presentation* presentation) : key(key),presentation(presentation){
}

Receiver::~Receiver(){
}

int Receiver::getKey(){
	return this->key;
}

Presentation* Receiver::getPresentation(){
	return this->presentation;
}