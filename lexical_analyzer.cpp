#include "lexical_analyzer.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

bool isPunctuator(char ch)
{
    return ch == ' ' || ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == ',' || ch == ';' || ch == '>' ||
           ch == '<' || ch == '=' || ch == '(' || ch == ')' ||
           ch == '[' || ch == ']' || ch == '{' || ch == '}' ||
           ch == '&' || ch == '|';
}

bool validIdentifier(char *str)
{
    if (isdigit(str[0]) || isPunctuator(str[0]))
        return false;
    int len = strlen(str);
    if (len == 1)
        return true;
    for (int i = 1; i < len; i++)
        if (isPunctuator(str[i]))
            return false;
    return true;
}

bool isOperator(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' ||
           ch == '/' || ch == '>' || ch == '<' ||
           ch == '=' || ch == '|' || ch == '&';
}

bool isKeyword(char *str)
{
    const char *keywords[] = {"if", "else", "while", "do", "break", "continue", "int", "double", "float", "return",
                              "char", "case", "long", "short", "typedef", "switch", "unsigned", "void", "static", "struct",
                              "sizeof", "volatile", "enum", "const", "union", "extern", "bool"};
    for (const char *keyword : keywords)
        if (!strcmp(str, keyword))
            return true;
    return false;
}

bool isNumber(char *str)
{
    int numOfDecimal = 0;
    if (strlen(str) == 0)
        return false;
    for (int i = 0; i < strlen(str); i++)
    {
        if (numOfDecimal > 1 && str[i] == '.')
            return false;
        else if (str[i] == '.')
            numOfDecimal++;
        if (!isdigit(str[i]) && !(str[i] == '-' && i == 0))
            return false;
    }
    return true;
}

char *subString(char *realStr, int l, int r)
{
    char *str = (char *)malloc(sizeof(char) * (r - l + 2));
    for (int i = l; i <= r; i++)
        str[i - l] = realStr[i];
    str[r - l + 1] = '\0';
    return str;
}

void parse(char *str)
{
    int left = 0, right = 0, count = 0;
    int len = strlen(str);
    while (right <= len && left <= right)
    {
        if (!isPunctuator(str[right]))
            right++;
        if (isPunctuator(str[right]) && left == right)
        {
            if (isOperator(str[right]))
                cout << str[right] << " IS AN OPERATOR\n";
            right++;
            left = right;
        }
        else if (isPunctuator(str[right]) && left != right || (right == len && left != right))
        {
            char *sub = subString(str, left, right - 1);
            if (isKeyword(sub))
                cout << sub << " IS A KEYWORD\n";
            else if (isNumber(sub))
                cout << sub << " IS A NUMBER\n";
            else if (validIdentifier(sub) && !isPunctuator(str[right - 1]))
                cout << sub << " IS A VALID IDENTIFIER\n";
            else if (!validIdentifier(sub) && !isPunctuator(str[right - 1]))
                cout << sub << " IS NOT A VALID IDENTIFIER\n";
            left = right;
        }
    }
}