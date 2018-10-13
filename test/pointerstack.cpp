/*
 * stack_pointer.cpp
 *
 *  Stack: pointer implementation
 *
 *  Created on: Jul 12, 2018
 *      Author: William Anderson
 *
 *
 */

#include "pointerstack.h"

#include <iostream>
using namespace StackPointer;

void StackPointer::display_stack(stack* S)
{
	node* q;

	printf("Current stack: \n");
	q = S->top;
	while ( q->next != NULL )
	{
		printf("[%d]->",q->value);
		q = q->next;
	}
	printf("NULL\n");
}

stack* StackPointer::MAKENULL(stack* S)
{
	if (S == NULL)
	{
		S = (stack*) malloc(sizeof(stack));	// Allocate memory
	}

	S->top = (node*) malloc(sizeof(node));

	if (S == NULL || S->top == NULL)
	{
		printf("Error: cannot allocate memory");
	}

	S->top->next = NULL; 	// Initialize top
	S->top->value = 0;

	return S;
}

bool StackPointer::EMPTY(stack* S)
{
	if (S->top->next == NULL)	// If top points to NULL
	{
		return true;
	} else {
		return false;
	}
}

node* StackPointer::TOP(stack* S)
{
	return S->top;
}

void StackPointer::POP(stack* S)
{
	node* temp;

	if (EMPTY(S))
	{
		printf("Error: stack is empty\n");
	} else {
		temp = S->top->next;				// Save reference
		S->top->value = S->top->next->value;// Copy value from next cell
		S->top->next = S->top->next->next;	// Copy link to next->next cell
		free(temp);							// Use reference to free memory
	}
}

bool StackPointer::FULL(stack* S)
{
	node* q = S->top;
	int i = 0;

	while (q->next != NULL && i >= maxlength)	// Count number of elements
	{											// until max length
		q->next = q->next->next;
		i++;
	}

	if (i > maxlength)
	{
		return true;							// Full if i > max
	} else {
		return false;							// Not full otherwise
	}
}

void StackPointer::PUSH(int x, stack* S)
{
	node* temp;

	if (FULL(S))
	{
		printf("Error: stack is full\n");
	} else {
		temp = S->top;							// Save reference to top
		S->top = (node*) malloc(sizeof(node));	// Allocate memory for new top
		S->top->value = x;						// Set value
		S->top->next = temp;					// Link to old top
	}

}
