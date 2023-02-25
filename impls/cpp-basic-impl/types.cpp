#include "types.h"

Token::~Token() {}

TokenList::TokenList(char start, char end) : startSymbol(start), endSymbol(end) {}

TokenSymbol::TokenSymbol(string v) : name(v) {}

TokenString::TokenString(string v) : value(v) {}

TokenNumber::TokenNumber(int v) : value(v) {}
