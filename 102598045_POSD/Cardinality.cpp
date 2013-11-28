#include "Cardinality.h"
#include <algorithm>
#include <RelationType.h>

using namespace std;

Cardinality::Cardinality(){
    this->cardinalityVector.push_back(RelationType::One);
    this->cardinalityVector.push_back(RelationType::Many);
}

vector<string> Cardinality::getCardinalityVector() const{
    return this->cardinalityVector;
}

bool Cardinality::hasCardinality(string cardinality){
    auto iterator = find(this->cardinalityVector.begin(),this->cardinalityVector.end(),cardinality);
    if(iterator != this->cardinalityVector.end())
        return true;
    return false;
}