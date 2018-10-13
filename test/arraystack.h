/*
 * stack_array.h
 *
 *  Created on: Jul 19, 2018
 *      Author: Juniper
 */

#ifndef ARRAYSTACK_H_
#define ARRAYSTACK_H_

namespace StackArray
{

	static const int maxlength = 1E6;

	typedef struct stack {
		int top;
		int elements[maxlength];
	} stack;

	void MAKENULL(stack* S);
	bool EMPTY(stack* S);
	int TOP(stack* S);
	void POP(stack* S);
	void PUSH(int x, stack* S);
	void display_stack(stack* S);

}

#endif /* ARRAYSTACK_H_ */
