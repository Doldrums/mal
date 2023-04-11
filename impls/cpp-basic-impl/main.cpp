#include <string>
#include <iostream>
#include <memory>

#include "lib.h"
#include "types.h"
#include "reader.h"
#include "printer.h"
#include "environment.h"

#include "core.cpp"

using namespace std;

string rep(const string &input, Environment *env);

int main(int argc, char *argv[])
{
    Environment *env = new Environment();

    for (const auto &pair : core::ns)
    {
        env->set(pair.first, pair.second);
    }
    string input;

    rep("(def! not (fn* (a) (if a false true)))", env);

    cout << "user> ";
    while (getline(cin, input))
    {
        std::cout << rep(input, env) << "\n";
        cout << "user> ";
    }
    return 0;
}

string rep(const string &input, Environment *env)
{
    try
    {
        return PRINT(EVAL(READ(input), env));
    }
    catch (const std::exception &e)
    {
        return string("Error: ") + e.what();
    }
}
