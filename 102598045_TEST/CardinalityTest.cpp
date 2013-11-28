#include "CardinalityTest.h"
#include "RelationType.h"

void CardinalityTest::SetUp(){
}

void CardinalityTest::TearDown(){
}

TEST_F(CardinalityTest,testHasCardinality){
    Cardinality cardinality;
    ASSERT_EQ(true,cardinality.hasCardinality(RelationType::One));
    ASSERT_EQ(true,cardinality.hasCardinality(RelationType::Many));
    ASSERT_EQ(false,cardinality.hasCardinality("X"));
}