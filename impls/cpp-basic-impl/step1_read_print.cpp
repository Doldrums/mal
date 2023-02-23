#include <string>
#include <iostream>
#include <memory>

#include "reader.cpp"
#include "printer.cpp"
#include "types.cpp"

using namespace std;

Token* READ(const string& input);
Token* EVAL(Token* ast);
string PRINT(Token* ast);
string rep(const string& input);

int main(int argc, char* argv[])
{
    string input;

    cout << "user> ";
    while (getline(cin, input)) {
        std::cout << rep(input) << "\n";
        cout << "user> ";
    }
    return 0;
}

string rep(const string& input)
{
    return PRINT(EVAL(READ(input)));
}

Token* READ(const string& input)
{
    return read_str(input);
}

Token* EVAL(Token* ast)
{
    return ast;
}

string PRINT(Token* ast)
{
    return pr_str(ast, true);
}
