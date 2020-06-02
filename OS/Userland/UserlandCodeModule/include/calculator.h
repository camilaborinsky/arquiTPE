#ifndef _CALCULATOR_H_
#define _CALCULATOR_H_

typedef struct token
{
    char header;
    double value;
} token;
int doubleToString(double value, char * buffer);
double stringToDouble(char * init, char * end);
void evaluator(char * in, char * out);
char infixToPosfix(token * infix, token * posfix);
char getPrecedence(char first, char second);
char tokenizer(char * in, token * out);
char isBracket(char tok);
char isOperator(char tok);
char isDigit(char tok);
char posfixEvaluator(token * expression, double * result);
double evaluateTok(double first, double sec, char op);

#endif

