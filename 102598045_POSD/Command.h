#pragma once

#include <gtest/gtest_prod.h> 

class Command{
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testUnexecute);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testUnexecute);
public:
    Command();
    virtual ~Command();
    void execute();
    void unExecute();
protected:
    virtual void doExecute() = 0;
    virtual void doUnExecute() = 0;
    bool getExecutionFalg();
private:
    bool executionFlag;
};