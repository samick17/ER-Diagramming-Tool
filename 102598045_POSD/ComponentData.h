#pragma once

#include <string>

using namespace std;

struct ComponentData{
public:
	ComponentData(string id,string name);
	~ComponentData();

	string getID();
	void setID(string id);
	string getName();
	void setName(string name);
private:
	string id;	
	string name;
};