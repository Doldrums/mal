#include <string>
#include <iostream>
#include <memory>

using namespace std;

string READ(const string& input);
string EVAL(const string& ast);
string PRINT(const string& ast);
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

string READ(const string& input)
{
    return input;
}

string EVAL(const string& ast)
{
    return ast;
}

string PRINT(const string& ast)
{
    return ast;
}
