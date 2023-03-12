#include <string>
#include <iostream>
#include <memory>

#include "types.h"
#include "reader.h"
#include "printer.h"
#include "environment.h"

using namespace std;

Token* READ(const string& input);
Token* EVAL(Token* ast, Environment& env);
string PRINT(Token* ast);
string rep(const string& input, Environment& env);

int main(int argc, char* argv[])
{
    Environment env = Environment();
    string input;

    env.set("+", new TokenFunction([](vector<Token*> args) -> Token* {
        double result = 0.0;

        for (auto arg : args) {
            TokenNumber* num = dynamic_cast<TokenNumber*>(arg);
            if (!num) {
                throw runtime_error("Argument to '+' must be a number");
            }
            result += num->value;
        }
        return new TokenNumber(result);
    }));

    env.set("-", new TokenFunction([](vector<Token*> args) -> Token* {
        TokenNumber* num = dynamic_cast<TokenNumber*>(args[0]);
        if (!num) {
            throw runtime_error("Argument to '-' must be a number");
        }
        double result = num->value;

        for (int i = 1; i < args.size(); i++) {
            TokenNumber* num = dynamic_cast<TokenNumber*>(args[i]);
            if (!num) {
                throw runtime_error("Argument to '-' must be a number");
            }
            result -= num->value;
        }
        return new TokenNumber(result);
    }));

    env.set("*", new TokenFunction([](vector<Token*> args) -> Token* {
        double result = 1.0;

        for (auto arg : args) {
            TokenNumber* num = dynamic_cast<TokenNumber*>(arg);
            if (!num) {
                throw runtime_error("Argument to '*' must be a number");
            }
            result *= num->value;
        }
        return new TokenNumber(result);
    }));

    env.set("/", new TokenFunction([](vector<Token*> args) -> Token* {
        TokenNumber* num = dynamic_cast<TokenNumber*>(args[0]);
        if (!num) {
            throw runtime_error("Argument to '/' must be a number");
        }
        double result = num->value;

        for (int i = 1; i < args.size(); i++) {
            TokenNumber* num = dynamic_cast<TokenNumber*>(args[i]);
            if (!num) {
                throw runtime_error("Argument to '/' must be a number");
            }
            result /= num->value;
        }
        return new TokenNumber(result);
    }));

    cout << "user> ";
    while (getline(cin, input)) {
        std::cout << rep(input, env) << "\n";
        cout << "user> ";
    }
    return 0;
}

string rep(const string& input, Environment& env) {
    try {
        return PRINT(EVAL(READ(input), env));
    } catch (const std::exception& e) {
        return string("Error: ") + e.what();
    }
}

Token* READ(const string& input)
{
    return read_str(input);
}

Token* eval_ast(Token* ast, Environment& env) {
    if (auto symbol = dynamic_cast<TokenSymbol*>(ast)) {
        auto name = symbol->name;
        return env.get(name);
    } else if (auto list = dynamic_cast<TokenList*>(ast)) {
        TokenList* result = new TokenList(list->startSymbol, list->endSymbol);
        for (auto& elem : list->list) {
            result->list.push_back(EVAL(elem, env));
        }
        return result;
    } else {
        return ast;
    }
}

Token* EVAL(Token* ast, Environment& env)
{
    if (TokenList* list = dynamic_cast<TokenList*>(ast)) {
        if (list->list.empty()) {
            return ast;
        }

        if (list->startSymbol == '[') {
            TokenList* result = new TokenList('[', ']');
            for (auto& elem : list->list) {
                result->list.push_back(EVAL(elem, env));
            }
            return result;
        } else if (list->startSymbol == '{') {
            TokenList* result = new TokenList('{', '}');
            for (int i = 0; i < list->list.size(); i += 2) {
                auto key = list->list[i];
                auto value = list->list[i + 1];
                auto evaluated_key = EVAL(key, env);
                auto evaluated_value = EVAL(value, env);
                result->list.push_back(evaluated_key);
                result->list.push_back(evaluated_value);
            }
            return result;
        }

        TokenList* evaledList = dynamic_cast<TokenList*>(eval_ast(ast, env));
        auto fn = evaledList->list[0];
        auto args = vector<Token*>(evaledList->list.begin() + 1, evaledList->list.end());
        if (TokenFunction* func = dynamic_cast<TokenFunction*>(fn)) {
            return func->fn(args);
        }

        throw runtime_error("Expected function, got " + pr_str(fn, true));
    } else {
        return eval_ast(ast, env);
    }
}

string PRINT(Token* ast)
{
    return pr_str(ast, true);
}
