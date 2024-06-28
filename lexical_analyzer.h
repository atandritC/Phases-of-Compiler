#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

bool isPunctuator(char ch);
bool validIdentifier(char *str);
bool isOperator(char ch); // Ensure this is declared here
bool isKeyword(char *str);
bool isNumber(char *str);
char *subString(char *realStr, int l, int r);
void parse(char *str);

#endif // LEXICAL_ANALYZER_H