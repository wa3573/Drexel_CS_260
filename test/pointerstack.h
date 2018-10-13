/*
 * stack_pointer.h
 *
 *  Created on: Jul 19, 2018
 *      Author: Juniper
 */

#ifndef POINTERSTACK_H_
#define POINTERSTACK_H_

namespace StackPointer
{

static const int maxlength = 100;

typedef struct node {
	int value;
	struct node* next;
} node;

typedef struct stack {
	node* top;
} stack;

void display_stack(stack* S);
stack* MAKENULL(stack* S);
bool EMPTY(stack* S);
node* TOP(stack* S);
void POP(stack* S);
bool FULL(stack* S);
void PUSH(int x, stack* S);

}


#endif /* POINTERSTACK_H_ */
