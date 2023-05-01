#include "array.h"

DataMap::DataMap() : arraySize(0), keys(nullptr), values(nullptr) {}

DataMap::~DataMap()
{
    clear();
}

void DataMap::insert(const string& key, const string& value)
{
    if (0 == arraySize && keys == nullptr && values == nullptr) {
        arraySize++;
        keys = new string[arraySize];
        values = new string[arraySize];
        keys[arraySize-1] = key;
        values[arraySize-1] = value; 
    }
    
    else {
        string *tempk = new string[++arraySize];
        string *tempv = new string[arraySize];
        for (int i = 0; i < arraySize - 1; i++) {
            tempk[i] = keys[i];
            tempv[i] = values[i];
        }
        tempk[arraySize - 1] = key;
        tempv[arraySize - 1] = value;
        delete[] keys;
        delete[] values;
        keys = tempk;
        values = tempv;
    }
}

string DataMap::find(const string& key) const
{
    
    for (int i = 0; i < arraySize; i++)
    {
        if (keys[i] == key) {
            return values[i]; }
    }
    return ""; // if key not found
}

void DataMap::clear()
{

    arraySize = 0;
    keys = nullptr;
    values = nullptr;
    
}
