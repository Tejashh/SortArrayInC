#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define QUIT "q"

const int MAX = 301;

typedef struct
{
    char *ss;
    int stackSize;
    int top;
} stack;

typedef stack * sPointer;
int debug= FALSE;

void stackPushing(sPointer st, char par)
{
    if (st->top >= MAX)
    {
        //double stack size
        printf ("\nYou need to create new Stack Brahhhhhh");
        char *temp;
        temp = (char *)malloc( sizeof(char) * (st->stackSize + 2));
        
        free(st->ss);
        
        st->ss = temp;
        st->ss += 2;
        
    }
    st->ss[++(st->top)] = par;
}
char stack_pop(stack * stk)
{
    if (stk->top <= -1)
        return '\0';
    return stk->ss[(stk->top)--];
}

int stack_is_empty (stack * st)
{
    if (st->top <= -1)
    {
        return TRUE;
    }
    return FALSE;
}

stack *Create (int n)
{
    stack *temp;
    temp = malloc (sizeof (stack)+2);
    if (temp == NULL)
    {
        printf ("Terminating\n");
        exit (1);
    }
    temp->ss = malloc (sizeof (char) * n+2);
    if (temp->ss == NULL)
    {
        printf("Terminating\n");
        exit (1);
    }
    temp->top = -1;
    return temp;
}

void Delete (stack *st)
{
    if(st == NULL)
        printf("NOT GOING TO WORK!!!!!!");
    else
    {
        if (st->ss)
        {
            free(st->ss);
        }
        free(st);
    }
}

int check_balance (char *exp, int *error_at){
    char paranthesis = '\0';
    char temp;
    int error = FALSE;
    int i =0;
    stack *stk;
    stk = Create (MAX);
    while (exp[i] != '\0')
    {
        paranthesis = exp[i];
        if (paranthesis == '(' || paranthesis == '{' || paranthesis == '[' || paranthesis == '<')
            stackPushing (stk, paranthesis);
        else if (paranthesis == ')' || paranthesis == '}' || paranthesis == ']'||  paranthesis == '>')
        {
            if (stack_is_empty (stk))
            {
                error = TRUE;
                break;
            }
            temp = stack_pop (stk);
            if (!((temp == '(' && paranthesis == ')') || (temp == '{' && paranthesis == '}')
                  ||(temp == '[' && paranthesis == ']')||(temp == '<' && paranthesis == '>')))
            {
                error = TRUE;
                break;
            }
        }
        i++;
    }
    if (!stack_is_empty (stk))
        error = TRUE;
    if ((error == TRUE) && (error_at != NULL))
        *error_at = i + 1;
    Delete (stk);
    return error;
}

int main (int argc, char *argv[])
{
    char exp[MAX];
    int  retval;
    int i;
    int  error_at;
    debug = FALSE;
    if( i > 2 ) {
        printf("Please use: %s[-d]\n", argv[0]);
        exit (0);
    }
    if( i == 2 && argv[1][0] == '-' && argv[1][1] == 'd' ) {
        printf("\nDebuging information\n");
        debug = TRUE;
    }
    while( !FALSE ) {
        printf("Enter your expression or type 'q' to leave: ");
        fgets(exp, MAX, stdin);
        if(exp[0]=='q')
        {
            exit (0);
        }
        retval = check_balance (exp, &error_at);
        if(retval == FALSE){
            printf ("\n%s\n",exp);
            printf ("\nExpression are balance:\n");
        }
        else
        {
            printf ("\nExpression is not balance:\n");
            printf ("\n%s\n",exp);
            printf("missing it's pair at %d\n",error_at);
        }
    }
    return 0;
}
