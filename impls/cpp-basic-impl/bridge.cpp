#include "bridge.h"
#include "types.h"
#include "bridge.pb.h"
#include "core.cpp"
#include "lib.h"
#include "environment.h"
#include <string>

using namespace std;
using namespace google;

bridge::Token *convertToProto(Token *token)
{
    bridge::Token *tokenProto = new bridge::Token();

    if (TokenSymbol *symbolToken = dynamic_cast<TokenSymbol *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_SYMBOL);
        bridge::TokenSymbol *symbolProto = new bridge::TokenSymbol();
        symbolProto->set_name(symbolToken->name);
        tokenProto->set_allocated_symbol(symbolProto);
    }
    else if (TokenKeyword *keywordToken = dynamic_cast<TokenKeyword *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_KEYWORD);
        bridge::TokenKeyword *keywordProto = new bridge::TokenKeyword();
        keywordProto->set_value(keywordToken->value);
        tokenProto->set_allocated_keyword(keywordProto);
    }
    else if (TokenString *stringToken = dynamic_cast<TokenString *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_STRING);
        bridge::TokenString *stringProto = new bridge::TokenString();
        stringProto->set_value(stringToken->value);
    }
    else if (TokenNumber *numberToken = dynamic_cast<TokenNumber *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_NUMBER);
        bridge::TokenNumber *numberProto = new bridge::TokenNumber();
        numberProto->set_value(numberToken->value);
        tokenProto->set_allocated_number(numberProto);
    }
    else if (TokenNil *nilToken = dynamic_cast<TokenNil *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_NIL);
        bridge::TokenNil *nilProto = new bridge::TokenNil();
        tokenProto->set_allocated_nil(nilProto);
    }
    else if (TokenTrue *trueToken = dynamic_cast<TokenTrue *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_TRUE);
        bridge::TokenTrue *trueProto = new bridge::TokenTrue();
        tokenProto->set_allocated_true_(trueProto);
    }
    else if (TokenFalse *falseToken = dynamic_cast<TokenFalse *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_FALSE);
        bridge::TokenFalse *falseProto = new bridge::TokenFalse();
        tokenProto->set_allocated_false_(falseProto);
    }
    else if (TokenList *listToken = dynamic_cast<TokenList *>(token))
    {
        tokenProto->set_type(bridge::TokenType::TT_LIST);
        bridge::TokenList *listProto = new bridge::TokenList();
        listProto->set_start_symbol(std::string(1, listToken->startSymbol));
        listProto->set_end_symbol(std::string(1, listToken->endSymbol));
        for (const auto &t : listToken->list)
        {
            *listProto->mutable_list()->Add() = *convertToProto(t);
        }
        tokenProto->set_allocated_list(listProto);
    }

    return tokenProto;
}

char *serialize_token(Token *token)
{
    bridge::Token *tokenProto = convertToProto(token);
    string serializedToken = tokenProto->SerializeAsString();
    char *serializedTokenCStr = new char[serializedToken.length() + 1];
    strcpy(serializedTokenCStr, serializedToken.c_str());
    return serializedTokenCStr;
}

void *init_enviroment()
{
    Environment *env = new Environment();

    for (const auto &pair : core::ns)
    {
        env->set(pair.first, pair.second);
    }
    return env;
}

char *parse_line(char *line)
{
    string input(line);
    Token *token = READ(input);
    return serialize_token(token);
}

char *eval_line(char *line, void *env)
{
    string input(line);
    Token *token = READ(input);
    Token *evaluatedToken = EVAL(token, (Environment *)env);
    string result = PRINT(evaluatedToken);

    char *resultCStr = new char[result.length() + 1];
    strcpy(resultCStr, result.c_str());
    return resultCStr;
}
