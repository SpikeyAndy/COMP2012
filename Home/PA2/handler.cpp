#include "handler.h"

HandlerModule::~HandlerModule() {
    if (languageFilter != nullptr) {
        languageFilter = nullptr;
    }
    if (toneFilter != nullptr) {
        toneFilter = nullptr;
    }
}

void HandlerModule::print() const
{
    std::cout << "Module name = " << m_name << ", this is a Handler, can handle topic = " << topic << std::endl;
}

void HandlerModule::trainData(const string &question, const string &answer) {
    this->data.insert(question, answer);
}


string HandlerModule::inneranswer(const string &question) const
{
    string answer = data.find(question);
    if (answer == "") {
        return "Sorry, I don't know";
    }
    else {
        return answer;
    }
}

string HandlerModule::answer(const string &question) const
{
    // First, check if the language filter is not null
    string translatedQuestion = question;
    if (languageFilter != nullptr && languageFilter->translatePreData(translatedQuestion) != "")
    {
        // Pass the question to the language filter and get the translated question
        translatedQuestion = languageFilter->translatePreData(question);
    }

    // Second, check if the tone filter is not null
    string filteredQuestion = translatedQuestion;
    if (toneFilter != nullptr && toneFilter->translatePreData(translatedQuestion) != "")
    {
        // Pass the translated question to the tone filter and get the filtered question
        filteredQuestion = toneFilter->translatePreData(translatedQuestion);
    }

    // Third, call the inneranswer method to find the answer within the data map
    string answer = inneranswer(filteredQuestion);

    // Fourth, check if the tone filter is not null
    string filteredAnswer = answer;
    if (toneFilter != nullptr && toneFilter->translatePostData(filteredAnswer) != "")
    {
        // Pass the answer to the tone filter and get the filtered answer
        filteredAnswer = toneFilter->translatePostData(filteredAnswer);
    }

    // Fifth, check if the language filter is not null
    string translatedAnswer = filteredAnswer;
    if (languageFilter != nullptr && languageFilter->translatePostData(translatedAnswer) != "")
    {
        // Pass the filtered answer to the language filter and get the translated answer
        translatedAnswer = languageFilter->translatePostData(translatedAnswer);
    }

    // Return the final answer
    return translatedAnswer;
}


HandlerMap::HandlerMap()
{
    arraySize = 0;
    names = nullptr;
    handlerModules = nullptr;
}

HandlerMap::~HandlerMap()
{
    clear();
}

void HandlerMap::insert(string key, HandlerModule *value)
{
    int index = -1;
    for (int i = 0; i < arraySize; ++i)
    {
        if (names[i] == key)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        // Add a new element to the arrays
        string *newNames = new string[arraySize + 1];
        HandlerModule **newHandlerModules = new HandlerModule *[arraySize + 1];

        for (int i = 0; i < arraySize; ++i)
        {
            newNames[i] = names[i];
            newHandlerModules[i] = handlerModules[i];
        }

        newNames[arraySize] = key;
        
        newHandlerModules[arraySize] = value;
        
        delete[] names;
        delete[] handlerModules;
        

        names = newNames;
        handlerModules = newHandlerModules;
        arraySize++;
    }
    else
    {
        // Update existing element
        handlerModules[index] = value;
    }
}

HandlerModule *HandlerMap::find(const string &key) const
{
    for (int i = 0; i < arraySize; ++i)
    {
        if (names[i] == key)
        {
            return handlerModules[i];
        }
    }
    return nullptr;
}

string HandlerMap::getNames(int index) const
{
    if (index >= 0 && index < arraySize)
    {
        return names[index];
    }
    else {return "";}
}

void HandlerMap::clear()
{

    arraySize = 0;
    if (names != nullptr) {
        delete[] names;
        names = nullptr;
    }
    if (handlerModules != nullptr) {
        delete[] handlerModules;
        handlerModules = nullptr;
    }
}
