#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "help.h"
#include "helpOrQuit.h"
#include "divideZero.h"
#include "isIllegal.h"
#include "illegal.h"

#define BUFFER 255

char stack[BUFFER], post[BUFFER];
int top = -1;


// Push function: adds char x to the top of the stack and increment the top value.
void push(char x)
{
	stack[++top]=x;
}

// Pop function: take one from the value of the stack's top index value.
char pop()
{
	return stack[top--];
}

// Order of operations.
int precedence(char p)
{
	if (p == '(')
		return 1;
	if (p == '+' || p =='-')
		return 2;
	if (p == '*' || p == '/')
		return 3;
	if (p == '^')
		return 4;
}

// Legal operators
int operator(int x)
{
	if (x == '+' || x == '-' || x == '*' || x == '/' || x == '^')
		return 1;
	else 
		return 0;
}

void calc()
{	
	// User input prompt
	printf(">>> ");
	char input[BUFFER] = "";
	fgets(input, 100, stdin);
	
	printf("Input: |%s|", input);
	
	char copy[BUFFER];
	int j = 0;
	int length = strlen(input);
	for (int i = 0; i <= length; i++)
	{
		if (!isspace(input[i]))
		{
			copy[j] = input[i];
			++j;
		}
	}
	printf("No Spaces: |%s|\n", copy);
	
	for (int i = 0; i < strlen(copy); ++i)
	{
		copy[i] = tolower(copy[i]);
	}
	//printf("\nLower string: |%s|", copy);
	
	// Check input for "h" or "q"
	if(helpOrQuit(copy))
		return;
	//printf("\nHELP/QUIT: %s", copy);
	
	// Print the error message if illegal input is detected
	if (isIllegal(copy) == 1)
	{
		illegal();
		return;
	}
	if (isIllegal(copy) == 2)
	{
		divideZero();
		return;
	}
	
	// Check for more than one decimal point per operand input.
	// If detected, print error message and return to start.
	int count = 0;
	for (int i = 0; i < strlen(copy); i++)
	{
		if (copy[i] == '.')
			count++;
		if (operator(copy[i]))
			count = 0;
		if (count == 2)
		{
			illegal();
			return;
		}	
	}

	// Convert from infix to postfix notation
	int l = strlen(copy);
	int k = 0;
	
	// Go through every element of the postfix expression
	for (int i = 0; i <= l; i++)
	{
		// If this element is an operator, add a space to the postfix expression.
		if (operator(copy[i]))
		{
			post[k++] = ' ';
			
			// As long as the current operator is of a lower precedence than the operator on the stack, 
			// add the top of stack to the postfix expression, followed by a space.
			while (precedence(copy[i]) <= precedence(stack[top]))
			{
				post[k++] = stack[top];
				pop();
				post[k++] = ' ';
			}
			push(copy[i]);
		}
		// If a left bracket is found, add straight to the stack.
		else if (copy[i] == '(')
		{
			push(copy[i]);
		}
		// If right bracket is detected, pop everything off the stack and onto the postfix expression
		// until the matching left bracket is found on the stack. Discard the brackets.
		else if (copy[i] == ')')
		{
			while (stack[top] != '(')
			{
				post[k++] = ' ';
				post[k++] = stack[top];
				pop();
			}
			pop();
		}
		else if (copy[i] == '\0')
		{
			while (top != -1)
			{
				post[k++] = ' ';
				post[k++] = stack[top];
				pop();
			}
		}
		else 
			post[k++] = copy[i];
	}
	post[k] = '\0';
	//printf("Postfix: %s\n", post);
	
	
	

	// Evaluate the postfix expression
	
	
	// Make the stack empty for use in the evaluation process
	top = -1;
	
	int lp = strlen(post);
	double x1, x2, ret;
	char string[] = "\0";
	char retc[] = "\0";
	//char x1c[BUFFER] = "", x2c[BUFFER] = "";
	
	

	for (int i = 0; i <= lp; i++)
		
		// If it is a number(operand), push straight to stack
		if (isdigit(post[i]))
		{
			push(post[i]);
			//printf("\nPost: %c\n", post[i]);
		}
		// If it is an operator, pop the two topmost operands from the stack and calculate
		else if (operator(post[i]))
		{
			string[0] = pop();
			// Convert the value to a floating point value
			x2 = atof(string);
			// Restore the string to be able to get the next value
			string[0] = "\0";
			string[0] = pop();
			x1 = atof(string);
			//printf("x1 = %f\n", x1);
			//printf("x2 = %f\n", x2);
			
			switch (post[i])
			{
				case '+': 
					ret = x1 + x2;
					//printf("1");
					break;
				case '-':
					ret = x1 - x2;
					//printf("2");
					break;
				case '*':
					ret = x1 * x2;
					//printf("3");
					break;
				case '/':
					ret = x1 / x2;
					//printf("4");
					if (x2 == 0)
					{
						divideZero();
						return;
					}
					break;
				case '^':
					ret = pow(x1,x2);
					//printf("5");
					break;
			}
			//printf("\nMade it to the end of the switch.");
			
			//printf("stack: |%s|\n", stack);
			sprintf(retc, "%f", ret);
			//printf("Sprintf: %f", retc);
			push(ret);
			//printf("stack: |%s|\n", stack);
		}

	//printf("stack: |%s|\n", stack);
	//printf("\nResult = %d", stack[top]);
	printf("%.3f\n", stack[top]);
}






