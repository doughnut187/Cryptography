/******************************************************************************
Encrypt a string (plain_in) using a string (key) and the XOR operator to create
a ciphertext (cipher) then decrypt the cipher using the same key and the XOR
operator to get the original plain_in back (plain_out)
*******************************************************************************/

#include <iostream>
#include <string>

using namespace std;

void remove_spaces(string& in_str) 
{
/*
Helper function to remove whitespace from the key
*/
    for(int i = 0; i < (int)in_str.size(); i++){
        if(isspace(in_str[i])) {
            in_str.erase(in_str.begin()+i);
        }
    }
}

void printBits(size_t const size, void const * const ptr)
{
/*
Helper function to print the binary representation of the ciphertext
*/
    unsigned char *b = (unsigned char*) ptr;
    unsigned char byte;
    
    for (int i = size-1; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
            byte = (b[i] >> j) & 1;
            printf("%u", byte);
        }
    }
}

void encrypt(string& key, string& plain_in, string& cipher) 
{
/*

*/
    char temp;
    int key_it = 0;
    int in_it = 0;
    for(int i = 0; i < (int)plain_in.size(); i++) {
        if(!isspace(plain_in[in_it])) {
            temp = (char)key[key_it] ^ (char)plain_in[in_it];
            cipher += temp;
            key_it++;
            in_it++;
        }else {
            cipher += '`';
            in_it++;
        }
    }
}

void decrypt(string& key, string& cipher, string& plain_out) 
{
/*

*/
    char temp;
    int key_it = 0;
    int in_it = 0;
    for(int i = 0; i < (int)cipher.size(); i++) {
        if(cipher[in_it] != '`') {
            temp = (char)key[key_it] ^ (char)cipher[in_it];
            plain_out += temp;
            key_it++;
            in_it++;
        }else {
            plain_out += ' ';
            in_it++;
        }
    }
}

int main()
{
/*
Asks for a message and a key. If the key is not longer than the message ask
to enter a new one, otherwise just repeat the key as many times as needed.
*/
    string key, plain_in, cipher, plain_out;
    cout << "Please enter your message: ";
    getline(cin, plain_in);
key_in:
    cout << "Please enter your key (needs to be longer than message): ";
    getline(cin, key);
    if(plain_in.size() > key.size()) {
        cout << "Key is not big enough, would you like to enter a new one? (y/n): ";
        string response;
        getline(cin, response);
        if(response == "y" || response == "yes"){
            goto key_in;
        }else {
            while(plain_in.size() > key.size()){
                key += key;
            }
        }
    }
    remove_spaces(key);
    encrypt(key, plain_in, cipher);
    cout << "cipher: ";
    for(int i = 0; i < (int)cipher.size(); i++){
        printBits(sizeof(cipher[i]), &cipher[i]);
    }
    cout << endl;
    decrypt(key, cipher, plain_out);
    cout << "plain out: " << plain_out << endl;

    return 0;
}
