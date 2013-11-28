#pragma once

#include <vector>
#include <string>

using namespace std;

class Cardinality{
public:
    Cardinality();
    vector<string> getCardinalityVector() const;
    bool hasCardinality(string cardinality);
private:
    vector<string> cardinalityVector;
};