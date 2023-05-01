#include "VigenereCipher.h"
#include "Utility.h"

// TODO #1
// Initialize the static data member alphabetSize here
const int VigenereCipher::alphabetSize = 26;

// TODO #2
// Implement the encrypt member function according to the given algoirthm.
string VigenereCipher::encrypt(string plaintextMsg) const {
    int length = key.length();
    string cipherText = "";
    int lengthOfPlaintext = plaintextMsg.length();
    for (int index = 0; index < lengthOfPlaintext; index++) {
        char c = 'a';
        if (isalpha(plaintextMsg[index])) {
            
            if (isupper(plaintextMsg[index])) {
                int offset = plaintextMsg[index] - 'A';
                c = 'a' + offset;
            } 
            else {
                c = plaintextMsg[index];
            }
            int shift = key[index % length] - 'a';
            c = c - 'a'; // to get the offset of c to add
            int shifted_value = static_cast<int>(c) + shift;
            shifted_value = shifted_value % alphabetSize; //make it within the alphabet
            shifted_value = shifted_value + 'a';
            c = static_cast<char>(shifted_value); //! for the 4th character, adding 22 (shift) to c (112) becomes -112 '/x84'
            // char z = 'z';
            // if (c > z) {
            //     c -= alphabetSize;
            // }      
            cipherText += c;
        }
        else {

            // if (plaintextMsg[index] == '.') {
            //     cipherText += plaintextMsg[index];
            //     return cipherText;
            //     }
            // else {
                cipherText += plaintextMsg[index];
            //}
            
        }
    }
    return cipherText;
}


// TODO #3
// Implement the decrypt member function according to the given algoirthm.
string VigenereCipher::decrypt(string ciphertextMsg) const {
    int length = key.length();
    string plainText = "";
    int lengthOfCiphertext = ciphertextMsg.length();

    for (int index = 0; index < lengthOfCiphertext; index++) {
        char c;
        if (isalpha(ciphertextMsg[index])) {
            if (isupper(ciphertextMsg[index])) {
                int offset = ciphertextMsg[index] - 'A';
                c = 'a' + offset;
            } 
            else {
                c = ciphertextMsg[index];
            }
            int shift = key[index % length] - 'a';
            c = c - 'a'; // to get the offset of c to add
            int shifted_value = static_cast<int>(c) - shift;
            shifted_value = shifted_value % alphabetSize; //make it within the alphabet
            shifted_value = shifted_value + 'a';
            int a = 'a';
            if (shifted_value < a) {
                shifted_value += alphabetSize;
            }
            c = static_cast<char>(shifted_value);
            
            plainText += c; 
        }
        
        else {

            // if (ciphertextMsg[index] == '.') {
            //     plainText += ciphertextMsg[index]; //! keeps adding additional characters after the fullstop
            //     return plainText;
            //     }
            // else {
                plainText += ciphertextMsg[index];
            //}
            
        }   
        }
    
    return plainText;
}



// TODO #4
// Implement the static member function generateRandomKey
// according to the given algorithm.
string VigenereCipher::generateRandomKey(int length) {
    string randomKey = "";
    char c;
    for (int i = 0; i < length; i++) {
        int randomValue = _rand() % alphabetSize;
        c = 'a' + randomValue;
        randomKey += c;
    }
    return randomKey;
}