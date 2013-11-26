#include "Cardinality.h"
#include <algorithm>

using namespace std;

vector<string> Cardinality::getCardinalityVector() const{
    return this->cardinalityVector;
}

void Cardinality::insertCardinality(string cardinality){
    this->cardinalityVector.push_back(cardinality);
}

bool Cardinality::hasCardinality(string cardinality){
    auto iterator = find(this->cardinalityVector.begin(),this->cardinalityVector.end(),cardinality);
    if(iterator != this->cardinalityVector.end())
        return true;
    return false;
}