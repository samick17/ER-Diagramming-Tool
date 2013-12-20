#include "Command.h"

class CutComponentsCommand : public Command{
public:
    CutComponentsCommand();
    ~CutComponentsCommand();
protected:
    void doExecute();
    void doUnExecute();
};