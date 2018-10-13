/*
 * list_array.h
 *
 *  Created on: Jul 19, 2018
 *      Author: Juniper
 */

#ifndef ARRAYLIST_H_
#define ARRAYLIST_H_

namespace ListArray
{
static const int maxlength = 1E6;

typedef struct {
	int elements[maxlength];
	int last;
} list;

int FIRST( list* L );
int END( list* L );
void MAKENULL( list* L );
int NEXT( int p, list* L );
int PREVIOUS( int p, list* L );
void INSERT( int x, int p, list* L );
void DELETE( int p, list* L );
int RETRIEVE(int p, list* L);
int LOCATE(int x, list* L);
void display_list(list* L);

}

#endif /* ARRAYLIST_H_ */
