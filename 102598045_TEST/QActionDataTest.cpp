#include "QActionDataTest.h"
#include "QActionData.h"
#include "ActionData.h"

void QActionDataTest::SetUp(){
}

void QActionDataTest::TearDown(){
}

string QActionDataTest::expectedToolTip(string name,string key){
    string toolTip = name;
    if(key != "")
        toolTip += "("+key+")";
    return toolTip;
}

TEST_F(QActionDataTest,testInitialToolTip){
    for(unsigned int index = ActionData::OpenFile;index <= ActionData::OpenFile+ActionData::ActionLength;index++){
        QActionData qActionData = QActionData(index);
        ASSERT_EQ(expectedToolTip(qActionData.getActionText(),qActionData.getKeySequence()),qActionData.initialToolTip(qActionData.getActionText(),qActionData.getKeySequence()));
    }
}