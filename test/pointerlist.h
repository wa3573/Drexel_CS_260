/*
 * list_pointer.h
 *
 *  Created on: Jul 19, 2018
 *      Author: Juniper
 */

#ifndef POINTERLIST_H_
#define POINTERLIST_H_

namespace ListPointer
{

typedef struct node { 	// Node fuctions both as element, and as list itself,
	int value;			// in the form of pointer to head
	struct node* next;
} node;

bool mem_error( node* p );
void display_list(node* head);
void display_list_memory(node* head);
void free_list(node* head);

node* FIRST( node* head );
node* END( node* head );
node* MAKENULL( node* head );
node* NEXT( int p, node* head ); // NEXT: given integer position
node* NEXT( node* p, node* head ); // NEXT: given node* position
node* PREVIOUS( int p, node* head ); // PREVIOUS: given integer position
node* PREVIOUS( node* p, node* head ); // PREVIOUS: given node* position
bool INSERT( int x, node* head ); // INSERT: append to end of list
bool INSERT( int x, node* p, node* head ); // INSERT: insert after node p
bool INSERT( int x, int p, node* head ); // INSERT: insert after position p
void DELETE( node* p, node* head );
void DELETE( node* p );
bool DELETE(int p, node* head);
node* RETRIEVE(node* p);
node* RETRIEVE(int p, node* head); // RETRIEVE: Given int position
node* RETRIEVE(node* p, node* head); // RETRIEVE: Given node* position
node* LOCATE(int x, node* head); // LOCATE: Given node* position


}

#endif /* POINTERLIST_H_ */
