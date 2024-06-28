#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
#include "lexical_analyzer.h"
#include "syntax_analyzer.h"

using namespace std;

int main()
{
    char c[MAXLEN];
    cout << "Enter expression: ";
    cin.getline(c, MAXLEN);
    if (!isValidExpression(c))
    {
        cout << "Invalid expression\n";
        return 1;
    }

    parse(c);

    Parser parser(c);
    Node *root = parser.parseStatement();

    ofstream fout("parse_tree.dot");
    fout << "digraph G {\n";
    root->printDOT(fout);
    fout << "}\n";
    fout.close();

    InfixToPostfix converter;
    string infix(c);
    string postfix = converter.convert(infix);
    cout << "Postfix expression: " << postfix << endl;

    return 0;
}