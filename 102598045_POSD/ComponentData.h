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

	bool operator==(const ComponentData& componentData) const;
private:
	string id;	
	string name;
};