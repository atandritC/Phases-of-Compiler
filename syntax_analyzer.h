#ifndef SYNTAX_ANALYZER_H
#define SYNTAX_ANALYZER_H

#include <stack>
#include <fstream>
#include <string>

const int MAXLEN = 100;

bool isOperand(char c);
bool isValidExpression(char c[]);

class Node
{
public:
    std::string label;
    Node *children[MAXLEN];
    int num_children;

    Node(std::string label);
    void addChild(Node *child);
    void printDOT(std::ofstream &fout);
};

class Parser
{
public:
    char *input;
    int pos;

    Parser(char *input);
    Node *parseStatement();
    Node *parseExpression();
    Node *parseTerm();
    Node *parseFactor();
};

class InfixToPostfix
{
public:
    int getPriority(char c);
    std::string convert(std::string infix);
};

#endif // SYNTAX_ANALYZER_H