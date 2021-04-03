//no reference

#include<stdio.h>
#include<stdint.h>
#include<string.h>

#define MAX 1000001

int32_t priority(char c);
int32_t postfix(char *str, double *post, int32_t length);
void push(double *stack, int32_t *top, double c);
double pop(double *stack, int32_t *top);

char arithmetic[MAX] = {0};
double post[MAX] = {0};
double operation[MAX] = {0};


int main()
{
    while(fgets(arithmetic, MAX, stdin) != NULL)
    {
        int32_t length = strlen(arithmetic);
        arithmetic[length - 1] = 0;
        postfix(arithmetic, post, length);
        printf("%.15lf\n", post[0]);
    }
    return 0;
}

int32_t postfix(char *str, double *post, int32_t length)
{
    int32_t top_p = 0;
    int32_t top_op = 0;
    for (int32_t i = 0; i < length; i++)
    {
        if(str[i] >= '0' && str[i] <= '9')
        {
            int32_t num = 0;
            for (; str[i] >= '0' && str[i] <= '9'; i++)
            {
                num = num * 10 + str[i] - '0';
            }
            i--;
            push(post, &top_p, num);
        }
        else if(top_op == 0 || priority(str[i]) > priority(operation[top_op - 1]))
        {
            push(operation, &top_op, str[i]);
        }
        else if(operation[top_op - 1] == '(')
        {
            if(str[i] == ')')
            {
                pop(operation, &top_op);
            }
            else
            {
                push(operation, &top_op, str[i]);
            }
        }
        else
        {
            char oper = pop(operation, &top_op);
            if( oper == '+' )
            {
                push(post, &top_p, pop(post, &top_p) + pop(post, &top_p) );
            }
            else if( oper == '-' )
            {
                push(post, &top_p, -1.0 * (pop(post, &top_p) - pop(post, &top_p)) );
            }
            else if( oper == '*' )
            {
                push(post, &top_p, pop(post, &top_p) * pop(post, &top_p) );
            }
            else//oper == '/'
            {
                push(post, &top_p, (1 / pop(post, &top_p)) * pop(post, &top_p) );
            }
            i--;
        }
    }

    return top_p;
}

int32_t priority(char c)
{
    if(c == '(')
    {
        return 3;
    }
    else if(c == '*' || c == '/')
    {
        return 2;
    }
    else if(c == '+' || c == '-')
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void push(double *stack, int32_t *top, double c)
{
    stack[*top] = c;
    *top += 1;
    return;
}

double pop(double *stack, int32_t *top)
{
    *top -= 1;
    return stack[*top];
}

