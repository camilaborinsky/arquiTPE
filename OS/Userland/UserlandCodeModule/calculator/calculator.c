#include <calculator.h>
#include <stdlib.h>

#define OPERATORS 8
#define NULLTERMINATED 0
#define NUMBER 1

char operators[OPERATORS] = {'+', '-', '*', '/', '%', '^', '(', ')'};
char mat[OPERATORS - 1][OPERATORS] = {
    {1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 1},
    {1, 1, 1, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 0, 0, 0}};

int doubleToString(double value, char * buffer){
	int precision=1000000000;
    int c=0;
    if(value<0){
        value=-value;
        buffer[c++]='-';
    }
	int m=value;
	double p = value-m;
	int r=(int)(p*precision+0.00001f);
	
	c += intToString(m,buffer+c);
	buffer[c++]='.';
	
	
	int aux=r;
	while(r!=0 && 10*aux/precision<1){
		buffer[c++]='0';
		aux*=10;
	}
	
	
	
	
	intToString(r,buffer+c++);
    buffer[c]=0;
    return c;
}

double stringToDouble(char *init, char *end)
{
    double res = 0;
    char comma = 0;
    double exp = 1.0f / 10;
    while (init < end)
    {

        if (*init == '.' || *init == ',')
        {
            comma = 1;
        }
        else if (comma)
        {
            res += (*init - '0') * exp;
            exp = exp / 10;
        }
        else
        {
            res = res * 10 + (*init - '0');
        }
        init++;
    }
    return res;
}

void evaluator(char *in, char * out)
{
    token toks[100];
    token posfix[100];
    double result = 0;

    char error = tokenizer(in, toks);
    error = infixToPosfix(toks, posfix);
    error = posfixEvaluator(posfix, &result);
    doubleToString(result,out);
    return result;
}

char posfixEvaluator(token *expression, double *result)
{
    double stack[100];
    int idx = 0;
    int exprIdx = 0;
    while (expression[exprIdx].header != NULLTERMINATED)
    {
        if (expression[exprIdx].header == NUMBER)
        {
            stack[idx] = expression[exprIdx].value;
            idx++;
            exprIdx++;
        }
        else
        {
            if (idx == 0)
            {
                return -1;
            }
            double aux1 = stack[--idx];
            if (idx == 0)
            {
                return -1;
            }
            double aux2 = stack[--idx];
            stack[idx] = evaluateTok(aux2, aux1, expression[exprIdx].header);
            idx++;
            exprIdx++;
        }
    }

    if (idx == 0)
    {
        return -1;
    }
    *result = stack[--idx];
    if (idx != 0)
    {
        return -1;
    }
}

char tokenizer(char *in, token *out)
{
    int signo = 1;
    int i = 0;
    int tokIdx = 0;
    int comma;
    while (in[i] != 0)
    {

        if (isOperator(in[i]) || isBracket(in[i]))
        {
            if(in[i]== '-' && isOperator(out[tokIdx-1].header)){
                signo = -1;
            }else{
                out[tokIdx].header = in[i];
                tokIdx++;
            }
            i++;
        }
        else if (isDigit(in[i]))
        {
            comma = 0;
            int j = i + 1;
            while (isDigit(in[j]) || in[j] == '.' || in[j] == ',')
            {
                if (in[j] == '.' || in[j] == ',')
                {
                    if (comma == 0)
                    {
                        comma = 1;
                    }
                    else
                    {
                        return -1;
                    }
                }

                j++;
            }
            out[tokIdx].header = NUMBER;
            out[tokIdx].value = stringToDouble(in + i, in + j)*signo;
            signo = 1;
            i = j;
            tokIdx++;
        }
        else if (in[i] == ' ')
        {
            do
            {
                i++;
            } while (in[i] == ' ');
        }
        else
        {
            return -1;
        }
    }
    out[tokIdx].header = NULLTERMINATED;
}

char infixToPosfix(token *infija, token *posfija)
{
    int i = 0;
    token tok;
    token stack[100];
    int idx = 0;
    int out = 0;
    while (infija[i].header != NULLTERMINATED)
    {
        tok = infija[i];
        if (isOperator(tok.header) || isBracket(tok.header))
        {
            if (idx == 0)
            {
                if (tok.header == ')')
                {
                    return -1;
                }
                stack[idx] = tok;
                idx++;
            }
            else
            {
                while ((idx != 0) && getPrecedence(stack[idx - 1].header, tok.header))
                {
                    posfija[out] = stack[--idx];
                    out++;
                }
                if (tok.header == ')')
                {
                    if (stack[idx - 1].header == '(')
                    {
                        idx--;
                    }
                    else
                    {
                        return -1;
                    }
                }
                else
                {
                    stack[idx++] = tok;
                }
            }
        }
        else
        {
            posfija[out++] = tok;
        }
        i++;
    }

    while (idx != 0)
    {
        if (isBracket(stack[idx - 1].header))
        {
            return -1;
        }
        else
        {
            posfija[out++] = stack[--idx];
        }
    }
    posfija[out].header = NULLTERMINATED;
    return out;
}

char getPrecedence(char first, char second)
{
    for (int i = 0; i < OPERATORS; i++)
    {
        if (first == operators[i])
        {
            first = i;
        }
        if (second == operators[i])
        {
            second = i;
        }
    }

    return mat[first][second];
}

char isBracket(char tok)
{
    return (tok == '(' || tok == ')');
}

char isOperator(char tok)
{
    for (int i = 0; i < OPERATORS - 2; i++)
    {
        if (tok == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

char isDigit(char tok)
{
    return tok >= '0' && tok <= '9';
}

double evaluateTok(double first, double second, char op)
{
    switch (op)
    {
    case '+':
        return first + second;
        break;
    case '-':
        return first - second;
        break;
    case '*':
        return first * second;
        break;
    case '/':
        return first / second;
        break;
    case '^':
        return 1;
        break;
    case '%':
        return 0;
        break;
    }
}
