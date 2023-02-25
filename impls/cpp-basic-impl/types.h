#pragma once

#include <string>
#include <vector>

using namespace std;

class Token {
public:
    virtual ~Token();
};

class TokenList : public Token {
public:
    TokenList(char start, char end);

    vector<Token*> list;
    char startSymbol;
    char endSymbol;
};

class TokenSymbol : public Token {
public:
    TokenSymbol(string v);

    string name;
};

class TokenString : public Token {
public:
    TokenString(string v);

    string value;
};

class TokenNumber : public Token {
public:
    TokenNumber(int v);

    int value;
};

class TokenNil : public Token {};
class TokenTrue : public Token {};
class TokenFalse : public Token {};
