/*
 * list_array.cpp
 *
 *	All implementations based on Aho's book. Most are self-explanatory
 *
 *	Stack: pointer implementation
 *
 *  Created on: Jul 11, 2018
 *      Author: William Anderson
 */

#include "arraylist.h"

#include <iostream>

using namespace ListArray;

int ListArray::FIRST( list* L )
{
	return 1;
}

int ListArray::END( list* L )
{
	return L->last + 1;
}

void ListArray::MAKENULL( list* L )
{
	L->last = 0;
}

int ListArray::NEXT( int p, list* L )
{
	if ( p + 1 <= END(L) && p > 0 ) // If argument is not the last cell
	{
		return p + 1;
	} else {
		return END(L); // Otherwise, return END(). Should be undefined, technically
	}
}

int ListArray::PREVIOUS( int p, list* L )
{
	if ( p <= END(L) && p > 1 ) // Similarly, if argument is position before one past last cell
	{
		return p - 1;
	} else {
		return 1; // Otherwise, return first cell. Should be undefined, technically
	}
}

void ListArray::INSERT( int x, int p, list* L )
{
	int i;

	for ( i = END(L); i >= p; i-- )
	{
		L->elements[i] = L->elements[i - 1];  // Shift all cells down one.
	}
	L->last = L->last + 1;
	L->elements[p-1] = x;
}

void ListArray::DELETE( int p, list* L )
{
	int i;
	for ( i = p; i < END(L); i++ )
	{
		L->elements[i - 1] = L->elements[i]; // Shift all cells up one.
	}

	L->last = L->last - 1;
}

int ListArray::RETRIEVE(int p, list* L)
{
	return L->elements[p-1]; 	// Note, returns one less than logical index,
								// to make use of elements[0]
}

int ListArray::LOCATE(int x, list* L)
{
	int i;
	i = FIRST(L); 			// Start at first
	while ( i <= END(L))	// While end is not reached
	{
		if ( i == x )
		{
			return i;
		}
	}

	return L->last + 1;
}

void ListArray::display_list(list* L)
{
	int p = FIRST(L);
	while (p != END(L))
	{
		std::cout << "[" << RETRIEVE(p, L) << "]->";
		p = NEXT(p, L);
	}
	std::cout << "END \n";
}

