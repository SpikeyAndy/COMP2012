#include "CipherUtility.h"

// TODO #5
// Implement the static member function isKeyValid
bool CipherUtility::isKeyValid(const Cipher* cipher){
    string a = cipher->key;
    for (int i = 0; i < a.length(); ++i) {
        if (!isalpha(a[i])) {
            return false;
        }
    }
    return true;
}


// TODO #6
// Implement the static member function removeNonAlphaCharsHelper
string CipherUtility::removeNonAlphaCharsHelper(string str){
    if (str == "") {
        return "";
    }
    else if (isalpha(str[0])) {
        string str2 = str.substr(1);
        string result = removeNonAlphaCharsHelper(str2);
        return str[0] + result;
    }
    else {
        string str2 = str.substr(1);
        return removeNonAlphaCharsHelper(str2);
    }
}
