#pragma once

#include <gtest/gtest_prod.h> 

class Command{
    friend class CommandTest;
    FRIEND_TEST(CommandTest,testExecute);
    FRIEND_TEST(CommandTest,testUnExecute);
    friend class AddNodeCommandTest;
    FRIEND_TEST(AddNodeCommandTest,testUnexecute);
    friend class ConnectNodeCommandTest;
    FRIEND_TEST(ConnectNodeCommandTest,testUnexecute);
    friend class DeleteComponentCommandTest;
    FRIEND_TEST(DeleteComponentCommandTest,testUnexecute);
    friend class EditTextOfComponentsCommandTest;
    FRIEND_TEST(EditTextOfComponentsCommandTest,testUnexecute);
    friend class SetPrimaryKeyCommandTest;
    FRIEND_TEST(SetPrimaryKeyCommandTest,testUnexecute);
    friend class DeleteMultiComponentCommandTest;
    FRIEND_TEST(DeleteMultiComponentCommandTest,testUnexecute);
    friend class MoveComponentsCommandTest;
    FRIEND_TEST(MoveComponentsCommandTest,testUnexecute);
    friend class PasteComponentsCommand;
    FRIEND_TEST(PasteComponentsCommandTest,testUnexecute);
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