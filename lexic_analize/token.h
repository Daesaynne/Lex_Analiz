#pragma once
#include <string>
using namespace std;

class Token
{
public:
    string tokenKeyName;
    string tokenKeyType; 

    Token()
    {
        tokenKeyName = "";
        tokenKeyType = "";
    }
    Token(const string& Name, const string& Type)
    {
        tokenKeyName = Name;
        tokenKeyType = Type;
    }

    string getTokenName() { return tokenKeyName; }
    string getTokenType() { return tokenKeyType; }

    string setTokenName(string newTokenName) { return (tokenKeyName = newTokenName);}
    string setTokenType(string newTokenType) { return (tokenKeyType = newTokenType);}
};
