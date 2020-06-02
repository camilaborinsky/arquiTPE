#ifndef _CALCULADORA_H_
#define _CALCULADORA_H_

typedef struct token
{
    char header;
    double value;
} token;

double stringToDouble(char * init, char * end);
double evaluator(char * in);
char infixToPosfix(token * infix, token * posfix);
char getPrecedence(char first, char second);
char tokenizer(char * in, token * out);
char isBracket(char tok);
char isOperator(char tok);
char isDigit(char tok);
char posfixEvaluator(token * expression, double * result);
double evaluateTok(double first, double sec, char op);

#endif

