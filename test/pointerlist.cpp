/*
 * main.cpp
 *
 *	List: pointer implementation
 *
 *  Created on: Jul 11, 2018
 *      Author: William Anderson
 */

#include "pointerlist.h"

#include <iostream>
using namespace ListPointer;

bool ListPointer::mem_error( node* p ) 	// Argument: pointer to memory which
{										// should be allocated
	if (p == NULL)
	{
		std::cout << "Error: cannot allocate memory \n";
		return true;
	}

	return false;						// Return: memory was successfully
}										// allocated or not

node* ListPointer::FIRST( node* head )
{
	return head;
}

node* ListPointer::END( node* head )
{
	node* q = head;

	while ( q->next != NULL)
	{
		q = q->next;
	}

	return q;
}

node* ListPointer::MAKENULL( node* head )
{
	if (head == NULL)							// If head is not already
	{											// allocated...
		head = (node*) malloc(sizeof(node)); 	// do so now
	}

	mem_error(head);							// Check allocation

	head->value = 0;							// Initialize head
	head->next = NULL;

	return head;
}

node* ListPointer::NEXT( int p, node* head ) // NEXT: given integer position
{
	int i = 1;
	node* temp = head;

	while(i < p)	// Traverse until position (int)p
	{
		temp = temp->next;
		i++;
	}

	return temp;
}

node* ListPointer::NEXT( node* p, node* head ) // NEXT: given node* position
{
	return p->next;
}

node* ListPointer::PREVIOUS( int p, node* head ) // PREVIOUS: given integer position
{
	int i = 1;
	node* temp = head;

	while(i < p - 2)	// Traverse until position (int)(p - 2)
	{
		temp = temp->next;
		i++;
	}

	return temp;
}

node* ListPointer::PREVIOUS( node* p, node* head ) // PREVIOUS: given node* position
{
	node* q = head;

	if (q == p)	// Head previous is itself, technically should be undefined
	{
		return head;
	}

	while (q->next != p)	// Traverse until cell points to cell entered as arg
	{
		q = q->next;
	}

	return q;
}


bool ListPointer::INSERT( int x, node* head ) // INSERT: append to end of list
{
	node* q = head;

	while (q->next != NULL)
	{
		q = q->next;
	}

	q->next = (node*) malloc(sizeof(node));

	mem_error(q->next);

	q->next->value = x;
	q->next->next = NULL;

	return true;
}

bool ListPointer::INSERT( int x, node* p, node* head ) // INSERT: insert after node p
{
	node* q = p;
	node* temp;

	temp = p->next;
	q->next = (node*) malloc(sizeof(node));

	mem_error(q->next);

	q->next->value = x;
	q->next->next = temp;

	return true;
}

bool ListPointer::INSERT( int x, int p, node* head ) // INSERT: insert after position p
{
	node* q = head;
	node* temp;
	int i = 1;

	while (i < p)
	{
		if (q->next->next == NULL)
		{
			return false;
		}
		q = q->next;
		i++;
	}

	if (q->next != NULL)
	{
		temp = q->next;
		q->next = (node*) malloc(sizeof(node));
		mem_error(q->next);
		q->next->value = x;
		q->next->next = temp;
	} else {
	q->next = (node*) malloc(sizeof(node));
	mem_error(q->next);
	q->next->value = x;
	q->next->next = NULL;
	}

	return true;
}

void ListPointer::DELETE( node* p, node* head )
{
	node* temp = NULL;

	if (p->next != NULL)
	{
		temp = p->next;				// Save reference to pointer
		p->next = p->next->next;	// Link over node
	}

	free(temp);						// Use reference to free allocated memory
}

void ListPointer::DELETE( node* p )	// Duplicate definition for different args
{
	node* temp = NULL;

	if (p->next != NULL)
	{
		temp = p->next;
		p->next = p->next->next;
	}

	free(temp);
}

bool ListPointer::DELETE(int p, node* head)
{
	node* temp;

	int i = 1;
	node* q = head;

	while (i < p)
	{
		if (q->next == NULL)
		{
			std::cout << "Error: index out of range";
			return false;
		}
		q = q->next;
		i++;
	}

	temp = q->next;
	q->next = q->next->next;
	free(temp);
	return true;
}

node* ListPointer::RETRIEVE(node* p)
{
	return p->next;
}

node* ListPointer::RETRIEVE(int p, node* head) // RETRIEVE: Given int position
{
	int i = 1;
	node* q = head;

	while (i < p and q->next != NULL)
	{
		q = q->next;
		i++;
	}

	if (i != p)
	{
		return NULL;
	}

	return q->next;
}

node* ListPointer::RETRIEVE(node* p, node* head) // RETRIEVE: Given node* position
{
	if (p == NULL)
	{
		return NULL;
	}

	return p->next;
}

node* ListPointer::LOCATE(int x, node* head) // LOCATE: Given node* position
{
	node* p = head;

	while (p->next != NULL)
	{
		if (p->next->value == x)
		{
			return p;
		} else {
			p = p->next;
		}
	}

	return NULL;
}

void ListPointer::display_list(node* head)
{
	node* p = FIRST(head);
	while (p != END(head))
	{
		std::cout << "[" << RETRIEVE(p, head)->value << "]->";
		p = NEXT(p, head);
	}
	std::cout << "END \n";
}

void ListPointer::display_list_memory(node* head)
{
	node* p = FIRST(head);
	while (p != END(head))
	{
		std::cout << "[" << RETRIEVE(p, head) << "]->";
		p = NEXT(p, head);
	}

	std::cout << "[" << RETRIEVE(p, head) << "]";

	std::cout << "(END) \n";
}

void ListPointer::free_list(node* head)
{
	node* q = head;
	node* temp = NULL;

	q = head;
	while (q->next != NULL)
	{
		temp = q->next;
		q->next = q->next->next;
		free(temp);
	}
	free(q->next);
	free(head);
}
