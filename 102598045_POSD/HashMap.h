#pragma once

#include <unordered_map>
#include <vector>
#include <algorithm>
#include "NoSuchKeyException.h"
#include "DuplicatedKeyException.h"
#include "CollectionType.h"

template<typename Key,typename Value>
class HashMap{
public:
	Value put(Key key,Value value);
	Value insertAt(Key key,Value value,unsigned int index);
	Value get(Key key);
	Value remove(Key key);
	unsigned int size();
	bool containsKey(Key key);
	Value getValueByIndex(unsigned int index);
	unsigned int getValueIndex(Value value);
	bool empty();
	void clear();
	
	typedef typename std::vector<Value>::iterator iterator;
	typedef typename std::vector<Value>::reverse_iterator reverse_iterator;
	iterator begin();
	iterator end();
	reverse_iterator rbegin();
	reverse_iterator rend();
private:	
	std::unordered_map<Key,Value> hashmap;
	std::vector<Value> valueVector;
};

template<typename Key,typename Value>
Value HashMap<Key,Value>::put(Key key,Value value){
	std::unordered_map<Key,Value>::iterator hashmapIterator = hashmap.find(key);	
	//contains Key
	if(hashmapIterator != hashmap.end())
		throw DuplicatedKeyException(CollectionType::TypeHashMap);
	hashmap.insert(pair<Key,Value>(key,value));	
	valueVector.push_back(value);

	return value;
}
//Insert Value at index
template<typename Key,typename Value>
Value HashMap<Key,Value>::insertAt(Key key,Value value,unsigned int index){
	std::unordered_map<Key,Value>::iterator hashmapIterator = hashmap.find(key);
	//contains Key
	if(hashmapIterator != hashmap.end())
		throw DuplicatedKeyException(CollectionType::TypeHashMap);
	hashmap.insert(pair<Key,Value>(key,value));	
	valueVector.insert(valueVector.begin()+index,value);

	return value;
}

template<typename Key,typename Value>
Value HashMap<Key,Value>::get(Key key){
	std::unordered_map<Key,Value>::iterator hashmapIterator = hashmap.find(key);	
	//no such key
	if(hashmapIterator == hashmap.end())
		throw NoSuchKeyException(CollectionType::TypeHashMap);	
	Value value = hashmapIterator->second;
	return value;
}

template<typename Key,typename Value>
Value HashMap<Key,Value>::remove(Key key){
	std::unordered_map<Key,Value>::iterator hashmapIterator = hashmap.find(key);	
	//no such key
	if(hashmapIterator == hashmap.end())
		throw NoSuchKeyException(CollectionType::TypeHashMap);	
	Value value = hashmapIterator->second;
	hashmap.erase(hashmapIterator);

	std::vector<Value>::iterator valueIterator = find(valueVector.begin(),valueVector.end(),value);
	valueVector.erase(valueIterator);
	
	return value;
}

template<typename Key,typename Value>
unsigned int HashMap<Key,Value>::size(){
	return hashmap.size();
}

template<typename Key,typename Value>
bool HashMap<Key,Value>::containsKey(Key key){
	std::unordered_map<Key,Value>::iterator hashmapIterator = hashmap.find(key);	
	if(hashmapIterator == hashmap.end())
		return false;
	return true;
}

template<typename Key,typename Value>
Value HashMap<Key,Value>::getValueByIndex(unsigned int index){
	if(index >= valueVector.size())
		throw CollectionException(CollectionType::TypeHashMap);
	return valueVector[index];
}
//get Value's index in hashmap
template<typename Key,typename Value>
unsigned int HashMap<Key,Value>::getValueIndex(Value value){
	vector<Value>::iterator valueIterator = find(valueVector.begin(),valueVector.end(),value);
	return std::distance(valueVector.begin(),valueIterator);
}

template<typename Key,typename Value>
bool HashMap<Key,Value>::empty(){
	return hashmap.empty();
}

template<typename Key,typename Value>
void HashMap<Key,Value>::clear(){
	hashmap.clear();
	valueVector.clear();
}

template<typename Key,typename Value>
typename HashMap<Key,Value>::iterator HashMap<Key,Value>::begin(){
	return valueVector.begin();
}

template<typename Key,typename Value>
typename HashMap<Key,Value>::iterator HashMap<Key,Value>::end(){
	return valueVector.end();
}
template<typename Key,typename Value>
typename HashMap<Key,Value>::reverse_iterator HashMap<Key,Value>::rbegin(){
	return valueVector.rbegin();
}

template<typename Key,typename Value>
typename HashMap<Key,Value>::reverse_iterator HashMap<Key,Value>::rend(){
	return valueVector.rend();
}