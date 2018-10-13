/*
 * main.cpp
 *
 *  Stack: array implementation
 *
 *  Very straightforward, implmented just as in Aho's book
 *  Comments are unnecessary here.
 *
 *  Created on: Jul 12, 2018
 *      Author: William Anderson
 *
 *
 */

#include "arraystack.h"

#include <iostream>
using namespace StackArray;

void StackArray::MAKENULL(stack* S)
{
	S->top = maxlength + 1;
}

bool StackArray::EMPTY(stack* S)
{
	if (S->top > maxlength)
	{
		return true;
	} else {
		return false;
	}
}

int StackArray::TOP(stack* S)
{
	if (EMPTY(S))
	{
		printf("Error: stack is empty\n");
		return 0;
	} else {
		return S->elements[S->top];
	}
}

void StackArray::POP(stack* S)
{
	if (EMPTY(S))
	{
		printf("Error: stack is empty\n");
	} else {
		S->top = S->top + 1;
	}
}

void StackArray::PUSH(int x, stack* S)
{
	if (S->top == 1)
	{
		printf("Error: stack is full\n");
	} else {
		S->top = S->top - 1;
		S->elements[S->top] = x;
	}
}

void StackArray::display_stack(stack* S)
{
	std::cout << "Current stack: \n";

	for (int i = S->top; i <= maxlength; i++)
	{
		std::cout << "[" << S->elements[i] << "]->";
	}

	std::cout << "NULL \n";
}
