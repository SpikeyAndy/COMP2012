#include "filter.h"

FilterModule::~FilterModule() {
    preData.clear();
    postData.clear();
}

void FilterModule::print() const {
    std::cout << "Module name = " << m_name << ", this is a filter, filter type = " << getFilterType(type) << std::endl;
}

void FilterModule::trainPreData(const string &source, const string &target) {
    preData.insert(source, target);
}

void FilterModule::trainPostData(const string &source, const string &target) {
    postData.insert(source, target);
}

string FilterModule::translatePreData(string question) const {
    string result = preData.find(question);
    if (result.empty()) {
        return "";
    } 
    else {
        return result;
    }
}

string FilterModule::translatePostData(string question) const {
    string result = postData.find(question);
    if (result.empty()) {
        return "";
    } 
    else {
        return result;
    }
}

//todo: Implementation
void FilterArray::insert(FilterModule *input)
{
    // Find if key already exists
    int index = -1;
    for (int i = 0; i < arraySize; ++i)
    {
        if (array[i] == input)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        // Add a new element to the arrays
        FilterModule **newFilterModules = new FilterModule *[arraySize + 1];

        for (int i = 0; i < arraySize; ++i)
        {
            newFilterModules[i] = array[i];
        }

        newFilterModules[arraySize] = input;
        
        delete [] array;

        array = newFilterModules;
        arraySize++;
    }
}

FilterModule* FilterArray::get(int index) const
{   
    if (index < 0 || index > arraySize)
    {
        return nullptr;
    }

    else {return array[index];}
}
