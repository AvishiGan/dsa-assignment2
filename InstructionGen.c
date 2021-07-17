#include <stdio.h>
#include <conio.h>
#include <ctype.h>

#define MAX 100    // Maximum Number of Elements in the Stack
#define OFFSET 200 // Symbolic Constant
#define NTC 5      // Number of Test Cases

int st[MAX]; // Implementing an Integer Stack
int top = -1;

// Function Declarations
void push(int st[], int val);
int pop(int st[]);
void getCommands(char exp[]);
void printOperation(char c);

int main()
{
    // char exp[100];
    // printf("Enter Postfix Expression : ");
    // gets(exp); // Reads the expression
    // getCommands(exp);

    // Test Data
    char exp[NTC][50] = {
        "ABC*+DE-/",
        "AB+CD+*",
        "AB*CD*+",
        "ABC*+D+",
        "AB+C*DE-FG+*-",
    };
    for (int i = 0; i < NTC; i++)
    {
        printf("TEST CASE %d : ", i + 1);
        printf(exp[i]);
        printf("\n---------------------------------\n");
        getCommands(exp[i]);
        printf("---------------------------------\n");
    }
    return 0;
}

// isOperator Function Definition: Check Whether the Character is an Operator
int isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// getCommands Function Definition: Print Instruction List
void getCommands(char exp[])
{
    int i = 0;
    int n = 0;
    int op1, op2;

    // Iterate Through the Expression Until the End of It
    while (exp[i] != '\0')
    {
        if (isOperator(exp[i]))
        {
            // pop Operands
            op2 = pop(st);
            op1 = pop(st);

            if (op1 > OFFSET) // Determine if op1 is a TEMP Variable
            {
                printf("LD TEMP%d\n", op1 - OFFSET); // LD TEMPn
            }
            else
            {
                printf("LD %c\n", op1); // LD A/B...
            }

            printOperation(exp[i]); // AD/SB/ML/DV

            if (op2 > OFFSET) // Determine if op2 is a TEMP Variable
            {
                printf("TEMP%d", op2 - OFFSET); // TEMPn
            }
            else
            {
                printf("%c", op2); // A/B...
            }

            printf("\n");
            n++;
            push(st, n + OFFSET);     // Push TEMPn to Stack
            printf("ST TEMP%d\n", n); // ST TEMPn
        }
        else
        {
            push(st, (int)exp[i]); // Push Operands into the Stack
        }
        i++;
    }
}

// printOperation Function Definition:
// Print the Corresponding Instruction for the Operation
void printOperation(char c)
{
    switch (c)
    {
    case '+':
        printf("AD ");
        break;
    case '-':
        printf("SB ");
        break;
    case '*':
        printf("ML ");
        break;
    case '/':
        printf("DV ");
        break;
    }
}

// push Function Definition: Push val to Stack
void push(int st[], int val)
{
    if (top == MAX - 1)
        printf("\n STACK OVERFLOW"); // Stack is Full
    else
    {
        top++;
        st[top] = val;
    }
}

// pop Function Definition: Pop Stack
int pop(int st[])
{
    int val = -1;
    if (top == -1)
        printf("\n STACK UNDERFLOW"); // Stack is Empty
    else
    {
        val = st[top];
        top--;
    }
    return val;
}
