#include <string>
#include <vector>
#include <sstream>

using namespace std;

#pragma once

class Token {
public:
    virtual ~Token() {}
};

class TokenList : public Token {
public:
    vector<Token*> list;
};

class TokenSymbol : public Token {
public:
    string name;
    TokenSymbol(string v) : name(v) {}
};

class TokenString : public Token {
public:
    string value;
    TokenString(string v) : value(v) {}
};

class TokenNumber : public Token {
public:
    int value;
    TokenNumber(int v) : value(v) {}
};

class TokenNil : public Token {};
class TokenTrue : public Token {};
class TokenFalse : public Token {};

string join(const vector<string>& strs, const string& sep) {
    stringstream ss;

    for (int i = 0; i < strs.size(); i++) {
        if (i > 0) {
            ss << sep;
        }
        ss << strs[i];
    }
    return ss.str();
}

std::string replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
