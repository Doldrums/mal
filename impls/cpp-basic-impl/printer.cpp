#include <regex>
#include <iostream>
#include <string>

#include "types.cpp"

using namespace std;

string pr_str(Token* elem, bool print_readably) {
    if (TokenSymbol* sym = dynamic_cast<TokenSymbol*>(elem)) {
        return sym->name;
    } else if (TokenNumber* num = dynamic_cast<TokenNumber*>(elem)) {
        return std::to_string(num->value);
    } else if (TokenList* list = dynamic_cast<TokenList*>(elem)) {
        std::vector<std::string> strs;
        for (Token* elem : list->list) {
            strs.push_back(pr_str(elem, print_readably));
        }
        return "(" + join(strs, " ") + ")";
    } else if (TokenString* str = dynamic_cast<TokenString*>(elem)) {
        if (print_readably) {
            std::string s = str->value;
            s = replace_all(s, "\\", "\\\\");
            s = replace_all(s, "\"=", "\\\"");
            s = replace_all(s, "\n", "\\n");
            return "\"" + s + "\"";
        } else {
            return str->value;
        }
    } else if (TokenNil* nil = dynamic_cast<TokenNil*>(elem)) {
        return "nil";
    } else if (TokenTrue* t = dynamic_cast<TokenTrue*>(elem)) {
        return "true";
    } else if (TokenFalse* f = dynamic_cast<TokenFalse*>(elem)) {
        return "false";
    } else {
        throw std::runtime_error("unrecognized Token");
    }
}
