#pragma once

#include <vector>
#include <string>

using namespace std;

class Cardinality{
public:
    vector<string> getCardinalityVector() const;
    void insertCardinality(string cardinality);
    bool hasCardinality(string cardinality);
private:
    vector<string> cardinalityVector;
};