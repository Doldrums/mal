#include <regex>
#include <iostream>
#include <string>

#include "types.cpp"

using namespace std;

class Reader {
public:
    Reader(std::vector<string>& tokens) : tokens_(tokens), index_(0) {}

    string next() {
        if (index_ >= tokens_.size()) {
            throw out_of_range("EOF while Reader::next()");
        }

        return tokens_[index_++];
    }

    string peek() {
        if (index_ >= tokens_.size()) {
            throw out_of_range("EOF while Reader::peek()");
        }

        return tokens_[index_];
    }

private:
    vector<string>& tokens_;
    size_t index_;
};


vector<string> tokenize(string str) {
    vector<string> matches;

    regex reg("[\\s,]*(~@|[\\[\\]{}()'`~^@]|\"(?:\\\\.|[^\\\\\"])*\"?|;.*|[^\\s\\[\\]{}('\"`,;)]*)");
    auto words_begin = sregex_iterator(str.begin(), str.end(), reg);
    auto words_end = sregex_iterator();

    for (sregex_iterator i = words_begin; i != words_end; ++i) {
        smatch match = *i;
        for (int i = 1; i < match.size(); i++) {
            if (match.str(i) != "") {
                matches.push_back(match.str(i));
            }
        }
    }

    return matches;
}

Token* read_form(Reader& r);

Token* read_list(Reader& r) {
    TokenList* list = new TokenList();
    r.next(); // consume the '('
    while (r.peek() != ")") {
        list->list.push_back(read_form(r));
    }
    r.next(); // consume the ')'
    return list;
}

Token* read_atom(Reader& r) {
    string token = r.next();
    if (token[0] == '"') {
        // string
        string str = token.substr(1, token.length() - 2);
        str = replace_all(str, "\\\"", "\"");
        str = replace_all(str, "\\n", "\n");
        str = replace_all(str, "\\\\", "\\");
        return new TokenString(str);
    } else if (token == "nil") {
        // nil
        return new TokenNil();
    } else if (token == "true") {
        // true
        return new TokenTrue();
    } else if (token == "false") {
        // false
        return new TokenFalse();
    } else if (std::all_of(token.begin(), token.end(), ::isdigit)) {
        // number
        return new TokenNumber(std::stoi(token));
    } else {
        // symbol
        return new TokenSymbol(token);
    }
}

Token* read_form(Reader& r) {
    string token = r.peek();
    if (token[0] == '(') {
        return read_list(r);
    } else {
        return read_atom(r);
    }
}

Token* read_str(string str) {
    auto tokens = tokenize(str);
    auto reader = Reader(tokens);

    return read_form(reader);
}
