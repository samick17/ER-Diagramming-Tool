#include "Command.h"
#include "Component.h"

class SetNodeNameCommand : public Command{
public:
	SetNodeNameCommand(Presentation* presentation,Component* node);
	~SetNodeNameCommand();

	void execute();
	void unExecute();
private:
	Component* node;
};