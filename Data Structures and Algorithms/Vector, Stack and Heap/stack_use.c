#include <stdio.h>
#include <string.h>
#include "stack.h"
#include "vector.h"
#define OK 0
#define NOT_OK 1
#define SAME 10
#define NOT_SAME 11
#define OPERTOR 100
#define NOT_OPERTOR 101

int IsStringOK(char _str[], Stack* _MyStack);
int IsTheSame (char _ch1, char _ch2);

int CalculatWithSteck(char _Infix[], Stack* _MyStack);
void InfixToPostfix(char _Infix[], Stack* _MyStack);
int NumOrOpertor(char _ch);
int CalculatPostfix(char _fixStr[], Stack* _MyStack);	

int main (void)
{
	int check, num;
	Stack* MyStack = StackCreate(15, 0);
	char str[] = {"(((}))"};
	check = IsStringOK (str, MyStack);
	printf ("%d\n", check);
	StackDestroy(MyStack);
	num = (int)'a';
	printf ("%d\n" ,num);
	return 0;
}

int CalculatWithSteck(char _Infix[], Stack* _MyStack)
{
	if (NOT_OK == IsStringOK(_Infix, _MyStack))
	{
		return;
	}
	InfixToPostfix(_Infix, _MyStack);
} 

void InfixToPostfix(char _Infix[], Stack* _MyStack)
{
	char fixStr[50]; 
	int i;
	int j = 0;
	for (i = 0; _Infix[i] != '\0'; i++)
	{
		if (NOT_OPERTOR == NumOrOpertor(_Infix[i]))
		{
			fixStr[j] 
			j++	
		}
		else
		{
		StackPush(MyStack, _Infix[i]);	
		}
	}
	strcpy(_Infix, fixStr);
}


int NumOrOpertor(char _ch)
{
	int ascii = (int)_ch;
	if (ascii == 42 || ascii == 43 ||ascii == 45 ||ascii == 47)
	{
		return OPERTOR;
	} 
	return NOT_OPERTOR;	
}

int IsStringOK(char _str[],Stack* _MyStack)
{
	int i, temp;
	for (i = 0; _str[i] != '\0'; i++)
	{
		if (_str[i] == '(' || _str[i] == '[' || _str[i] == '{')
		{
			StackPush(_MyStack, _str[i]);		
		}
		if (_str[i] == ')' || _str[i] == ']' || _str[i] == '}')
		{
			if (EMPTY == StackIsEmpty(_MyStack))
			{
				return NOT_OK;
			}
			StackPop(_MyStack, &temp);
			if (NOT_SAME == IsTheSame(temp, _str[i]))
			{
				return NOT_OK; 
			} 
		}
	}
	if (EMPTY != StackIsEmpty(_MyStack))
	{
		return NOT_OK;  
	}
	return OK;			
}

int IsTheSame (char _ch1, char _ch2)
{
	if (_ch1 == '(' && _ch2 == ')')
	{
		return SAME; 
	}
	if (_ch1 == '[' && _ch2 == ']')
	{
		return SAME; 
	}
	if (_ch1 == '{' && _ch2 == '}')
	{
		return SAME; 
	}    
	return NOT_SAME; 
} 







