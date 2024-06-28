#include "syntax_analyzer.h"
#include "lexical_analyzer.h" // Include lexical_analyzer.h to use isOperator
#include <iostream>

using namespace std;

bool isOperand(char c)
{
    return isdigit(c);
}

bool isValidExpression(char c[])
{
    stack<char> stk;
    int n = strlen(c);
    for (int i = 0; i < n; i++)
    {
        if (isOperand(c[i]))
        {
            if (!isOperator(c[i + 1]) && c[i + 1] != ')' && i != n - 1)
                return false;
        }
        else if (isOperator(c[i]))
        {
            if (c[i + 1] == ')' || i == n - 1)
                return false;
        }
        else if (c[i] == '(')
        {
            stk.push(c[i]);
        }
        else if (c[i] == ')')
        {
            if (stk.empty() || stk.top() != '(')
                return false;
            stk.pop();
        }
    }
    return stk.empty();
}

Node::Node(string label)
{
    this->label = label;
    num_children = 0;
}

void Node::addChild(Node *child)
{
    children[num_children++] = child;
}

void Node::printDOT(ofstream &fout)
{
    fout << "\"" << this << "\" [label=\"" << label << "\"]" << endl;
    for (int i = 0; i < num_children; i++)
    {
        fout << "\"" << this << "\" -> \"" << children[i] << "\"" << endl;
        children[i]->printDOT(fout);
    }
}

Parser::Parser(char *input)
{
    this->input = input;
    pos = 0;
}

Node *Parser::parseStatement()
{
    if (strncmp(input + pos, "if", 2) == 0)
    {
        pos += 2;
        Node *cond = parseExpression();
        Node *body = parseStatement();
        Node *node = new Node("if");
        node->addChild(cond);
        node->addChild(body);
        return node;
    }
    else if (strncmp(input + pos, "while", 5) == 0)
    {
        pos += 5;
        Node *cond = parseExpression();
        Node *body = parseStatement();
        Node *node = new Node("while");
        node->addChild(cond);
        node->addChild(body);
        return node;
    }
    else if (strncmp(input + pos, "for", 3) == 0)
    {
        pos += 3;
        Node *init = parseExpression();
        Node *cond = parseExpression();
        Node *step = parseExpression();
        Node *body = parseStatement();
        Node *node = new Node("for");
        node->addChild(init);
        node->addChild(cond);
        node->addChild(step);
        node->addChild(body);
        return node;
    }
    else if (input[pos] == '{')
    {
        pos++;
        Node *node = new Node("block");
        while (input[pos] != '}')
        {
            node->addChild(parseStatement());
        }
        pos++;
        return node;
    }
    else
    {
        Node *node = parseExpression();
        if (input[pos] == '=')
        {
            pos++;
            Node *value = parseExpression();
            Node *assign = new Node("=");
            assign->addChild(node);
            assign->addChild(value);
            return assign;
        }
        else
        {
            return node;
        }
    }
}

Node *Parser::parseExpression()
{
    Node *node = parseTerm();
    while (input[pos] == '+' || input[pos] == '-')
    {
        char op = input[pos++];
        Node *rhs = parseTerm();
        Node *new_node = new Node(string(1, op));
        new_node->addChild(node);
        new_node->addChild(rhs);
        node = new_node;
    }
    return node;
}

Node *Parser::parseTerm()
{
    Node *node = parseFactor();
    while (input[pos] == '*' || input[pos] == '/')
    {
        char op = input[pos++];
        Node *rhs = parseFactor();
        Node *new_node = new Node(string(1, op));
        new_node->addChild(node);
        new_node->addChild(rhs);
        node = new_node;
    }
    return node;
}

Node *Parser::parseFactor()
{
    if (isdigit(input[pos]))
    {
        string number;
        while (isdigit(input[pos]))
        {
            number += input[pos++];
        }
        return new Node(number);
    }
    else if (input[pos] == '(')
    {
        pos++;
        Node *node = parseExpression();
        pos++;
        return node;
    }
    else
    {
        string ident;
        while (isalnum(input[pos]))
        {
            ident += input[pos++];
        }
        return new Node(ident);
    }
}

int InfixToPostfix::getPriority(char c)
{
    switch (c)
    {
    case '-':
    case '+':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return 0;
}

string InfixToPostfix::convert(string infix)
{
    stack<char> stk;
    stk.push('#');
    string postfix;
    for (char &ch : infix)
    {
        if (isalpha(ch))
            postfix += ch;
        else if (ch == '(')
            stk.push('(');
        else if (ch == ')')
        {
            while (stk.top() != '#' && stk.top() != '(')
            {
                postfix += stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else
        {
            if (getPriority(ch) > getPriority(stk.top()))
                stk.push(ch);
            else
            {
                while (stk.top() != '#' && getPriority(ch) <= getPriority(stk.top()))
                {
                    postfix += stk.top();
                    stk.pop();
                }
                stk.push(ch);
            }
        }
    }
    while (stk.top() != '#')
    {
        postfix += stk.top();
        stk.pop();
    }
    return postfix;
}