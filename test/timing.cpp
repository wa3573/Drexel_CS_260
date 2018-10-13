/*
 * main.cpp
 *
 * Test all implementations for given input size, also test each implementation
 * for simple functionality.  Usage, 'timing <imp> <n>' or 'timing test_<imp>'
 *
 *  Created on: Jul 19, 2018
 *      Author: William Anderson
 *
 *      CSV output: implementation, n, push_avg, top_avg, insert_end_avg, ...
 *      insert_front_avg, delete_end_avg, delete_front_avg, traverse_avg
 *
 *
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <chrono>
#include <list>
#include <stack>
#include <fstream>
#include "arraylist.h"
#include "arraystack.h"
#include "pointerlist.h"
#include "pointerstack.h"

#define OUTPUT_FILE "out.csv"

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

using std::string;

int main(int argc, char** argv)
{
	std::string arg1;
	std::string arg2;

	static volatile int n;
	static volatile int runs = 100;

	std::string::size_type size_string;

	std::ofstream file_out;

	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << "<test type> <size of input>" << std::endl;
		exit(EXIT_SUCCESS);
	} else if (argc == 2) {
		arg1 = (std::string) argv[1];
	} else if (argc == 3)
	{
		arg1 = (std::string) argv[1];
		arg2 = (std::string) argv[2];
		n = std::stoi(arg2, &size_string, 10);
	} else {
		std::cout << "Usage: " << argv[0] << "<test type> <size of input>" << std::endl;
		exit(EXIT_SUCCESS);
	}

	if (arg1.compare("sa") == 0) // Stack, Array
	{
		using namespace StackArray;

		StackArray::stack* S;
		int i;
		int j;
		unsigned long int push_avg = 0;
		unsigned long int pop_avg = 0;
		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		S = (StackArray::stack*) std::malloc(sizeof(StackArray::stack));

		std::cout << KGRN "\n---- Stack, array implementation ----\n" KNRM;

		std::cout << "MAKENULL...\n";
		StackArray::MAKENULL( S );

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				StackArray::PUSH( i, S);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			push_avg = push_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				StackArray::POP(S);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			pop_avg = pop_avg + elapsed.count();
		}

		push_avg = push_avg / runs;
		pop_avg = pop_avg / runs;

		std::cout << "Push average = " << push_avg  << " ns " << std::endl;
		std::cout << "Pop average  = " << pop_avg  << " ns " << std::endl;

		// CSV output: implementation, n, push_avg, top_avg, insert_end_avg, insert_front_avg, delete_end_avg, delete_front_avg, traverse_avg

		file_out.open(OUTPUT_FILE, std::ios::app);
		file_out << arg1 << "," << n << "," << push_avg << "," << pop_avg << "\n";
		file_out.close();

		std::free(S);

	} else if (arg1.compare("sp") == 0) { // Stack, Pointers

		using namespace StackPointer;

		int i;
		int j;

		unsigned long int push_avg = 0;
		unsigned long int pop_avg = 0;

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		StackPointer::stack* S = NULL;

		std::cout << KGRN "\n---- Stack, pointer implementation ----\n" KNRM;

		std::cout << "MAKENULL...\n";
		S = StackPointer::MAKENULL( S );

		std::cout << "\nTest: iterated push\n";

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				StackPointer::PUSH( i, S);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			push_avg = push_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				StackPointer::POP(S);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			pop_avg = pop_avg + elapsed.count();
		}

		push_avg = push_avg / runs;
		pop_avg = pop_avg / runs;

		std::cout << "Push average = " << push_avg  << " ns " << std::endl;
		std::cout << "Pop average  = " << pop_avg  << " ns " << std::endl;

		file_out.open(OUTPUT_FILE, std::ios::app);
		file_out << arg1 << "," << n << "," << push_avg << "," << pop_avg << "\n";
		file_out.close();

		std::free(S);

	} else if (arg1.compare("la") == 0) { // List, Array

		using namespace ListArray;

		int i;
		int j;
		int p;
		list* L;

		runs = 1000;

		unsigned long int insert_end_avg = 0;
		unsigned long int insert_front_avg = 0;
		unsigned long int traverse_avg = 0;
		unsigned long int delete_end_avg = 0;
		unsigned long int delete_front_avg = 0;

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		L = (ListArray::list*) std::malloc(sizeof(list));

		std::cout << KGRN "\n---- List, array implementation ----\n" KNRM;

		printf("MAKENULL...\n");
		MAKENULL( L );

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now(); // Insert

			for ( i = 1; i <= n; i++ )
			{
				INSERT(i, END(L), L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			insert_end_avg = insert_end_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Traverse

			p = FIRST(L);

			while ( p != END(L))
			{
				p = NEXT(p, L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			traverse_avg = traverse_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Delete

			for ( i = 1; i <= n; i++ )
			{
				DELETE(PREVIOUS(END(L), L), L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			delete_end_avg = delete_end_avg + elapsed.count();
		}

		insert_end_avg = insert_end_avg / runs;
		delete_end_avg = delete_end_avg / runs;
		traverse_avg = traverse_avg / runs;
		std::cout << "Insertion from end average   = " << insert_end_avg  << " ns " << std::endl;
		std::cout << "Traversal average            = " << traverse_avg  << " ns " << std::endl;
		std::cout << "Deletion from end average    = " << delete_end_avg  << " ns " << std::endl;

		runs = 10;

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				INSERT(i, FIRST(L), L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			insert_front_avg = insert_front_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				DELETE(FIRST(L), L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			delete_front_avg = delete_front_avg + elapsed.count();
		}

		insert_front_avg = insert_front_avg / runs;
		delete_front_avg = delete_front_avg / runs;
		std::cout << "Insertion from front average = " << insert_front_avg  << " ns " << std::endl;
		std::cout << "Deletion from front average  = " << delete_front_avg  << " ns " << std::endl;

		// CSV output: implementation, n, push_avg, top_avg, insert_end_avg, insert_front_avg, delete_end_avg, delete_front_avg, traverse_avg

		file_out.open(OUTPUT_FILE, std::ios::app);
		file_out << arg1 << "," << n << ",,," << insert_end_avg << "," << insert_front_avg << "," << delete_end_avg << "," << delete_front_avg << "," << traverse_avg << "\n";
		file_out.close();

		std::free(L);

	} else if (arg1.compare("lp") == 0) { // List, Pointers
		using namespace ListPointer;

		node* q = NULL;
		node* p = NULL;
		int i;
		int j;
//		runs = 1000;

		unsigned long int insert_end_avg = 0;
		unsigned long int insert_front_avg = 0;
		unsigned long int traverse_avg = 0;
		unsigned long int delete_end_avg = 0;
		unsigned long int delete_front_avg = 0;

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		ListPointer::node* L = NULL;

		std::cout << KGRN "\n---- List, pointer implementation ----\n" KNRM;

		printf("MAKENULL...\n");
		if ((L = MAKENULL( L )) == NULL)
		{
			exit(EXIT_FAILURE);
		}


		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				q = L;

				if (q->next != NULL)
				{
					while ( q->next->next != NULL )
					{
						q = q->next;
					}
				}

				INSERT(i, q, L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			insert_end_avg = insert_end_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				q = L;

				if (q->next != NULL)
				{
					while ( q->next->next != NULL )
					{
						q = q->next;
					}
				}

				DELETE(q);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			delete_end_avg = delete_end_avg + elapsed.count();
		}

		insert_end_avg = insert_end_avg / runs;
		delete_end_avg = delete_end_avg / runs;
		std::cout << "Insertion from end average   = " << insert_end_avg  << " ns " << std::endl;
		std::cout << "Deletion from end average    = " << delete_end_avg  << " ns " << std::endl;

		runs = 10;

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				INSERT(i, FIRST(L), L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			insert_front_avg = insert_front_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Traverse

			p = FIRST(L);

			while ( p->next != NULL)
			{
				p = NEXT(p, L);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			traverse_avg = traverse_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Delete, front

			for ( i = 1; i <= n; i++ )
			{
				DELETE(FIRST(L));
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			delete_front_avg = delete_front_avg + elapsed.count();
		}

		insert_front_avg = insert_front_avg / runs;
		traverse_avg = traverse_avg / runs;
		delete_front_avg = delete_front_avg / runs;
		std::cout << "Insertion from front average = " << insert_front_avg  << " ns " << std::endl;
		std::cout << "Traversal average            = " << traverse_avg  << " ns " << std::endl;
		std::cout << "Deletion from front average  = " << delete_front_avg  << " ns " << std::endl;

		file_out.open(OUTPUT_FILE, std::ios::app);


		file_out << arg1 << "," << n << ",,," << insert_end_avg << "," << insert_front_avg << "," << delete_end_avg << "," << delete_front_avg << "," << traverse_avg << "\n";

		file_out.close();

		free_list(L);
	} else if (arg1.compare("test_la") == 0) {
		std::cout << KRED << "\n\n\t---- List, array implementation ----\n" << KNRM;

		int i;
		ListArray::list* L;

		L = (ListArray::list*) std::malloc(sizeof(ListArray::list));

		printf(KGRN "-->> MAKENULL... <<--\n" KNRM);
		MAKENULL( L );
		printf("Last = %d\n", END(L));
		display_list(L);

		printf(KGRN "-->> INSERT 1 element @ 1... <<--\n" KNRM);
		INSERT( 5, 1, L );
		printf("Last = %d\n", END(L));
		display_list(L);

		printf(KGRN "-->> INSERT 1 element @ 2... <<--\n" KNRM);
		INSERT( 5, 2, L );
		printf("Last = %d\n", END(L));
		display_list(L);

		printf(KGRN "-->> RETRIEVE element @ 1... <<--\n" KNRM);
		printf("Element 1 = %d\n", RETRIEVE( 1, L));

		printf(KGRN "-->> INSERT 5 elements at p = i...\n");
		for ( i = 1; i < 6; i++ )
		{
			INSERT( 4 * i, i, L);
		}

		printf(KGRN "-->> RETRIEVE 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			printf("Element %d = %d\n", i, RETRIEVE(i,L));
		}

		display_list(L);

		printf("5th value = %d \n", RETRIEVE(5, L));


		printf(KGRN "-->> Inserting 45 at position 5... <<-- \n" KNRM);
		INSERT(45, 5, L);
		printf("5th value = %d \n", RETRIEVE(5, L));
		printf("5th place, previous = %d \n", RETRIEVE(PREVIOUS(5, L), L));
		printf("5th place, next = %d \n", RETRIEVE(NEXT(5, L), L));
		printf("PREVIOUS(END) = %d \n", RETRIEVE(PREVIOUS(END(L), L), L));
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L), L) << "\n";
		printf("FIRST = %d \n", RETRIEVE(FIRST(L), L));

		display_list(L);


		printf(KGRN "-->> Deleting 45 at position 5... <<-- \n" KNRM);
		DELETE(5, L);
		printf("5th value = %d \n", RETRIEVE(5, L));
		printf("5th place, previous = %d \n", RETRIEVE(PREVIOUS(5, L), L));
		printf("5th place, next = %d \n", RETRIEVE(NEXT(5, L), L));
		printf("PREVIOUS(END) = %d \n", RETRIEVE(PREVIOUS(END(L), L), L));
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L), L) << "\n";
		printf("FIRST = %d \n", RETRIEVE(FIRST(L), L));

		display_list(L);


		printf(KGRN "-->> Deleting from end... <<-- \n" KNRM);
		DELETE(END(L), L);
		printf("PREVIOUS(END) = %d \n", RETRIEVE(PREVIOUS(END(L), L), L));
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L), L) << "\n";
		printf("FIRST = %d \n", RETRIEVE(FIRST(L), L));

		display_list(L);


		printf(KGRN "-->> Deleting from end...  <<--\n" KNRM);
		DELETE(END(L), L);
		printf("PREVIOUS(END) = %d \n", RETRIEVE(PREVIOUS(END(L), L), L));
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L), L) << "\n";
		printf("FIRST = %d \n", RETRIEVE(FIRST(L), L));

		display_list(L);

		printf(KGRN "-->> Deleting from first...  <<--\n" KNRM);
		DELETE(FIRST(L), L);
		printf("FIRST() value = %d \n", RETRIEVE(FIRST(L), L));
		printf("NEXT(FIRST) = %d \n", RETRIEVE(NEXT(FIRST(L), L), L));
		std::cout << "Position of NEXT(FIRST) = " << NEXT(FIRST(L), L) << "\n";
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L), L) << "\n";

		display_list(L);

		} else if (arg1.compare("test_lp") == 0) {

		int i;

		std::cout << KRED << "\n\n\t---- List, pointer implementation ----\n" << KNRM;

		ListPointer::node* L_P = NULL;

		printf(KGRN "-->> MAKENULL... <<--\n " KNRM);
		if ((L_P = MAKENULL( L_P )) == NULL)
		{
			exit(EXIT_FAILURE);
		}
		printf("END = %p\n", END(L_P));

		printf(KGRN "-->> INSERT 1 element... <<--\n" KNRM);
		INSERT( 5, L_P );
		printf("END = %p\n", END(L_P));

		printf(KGRN "-->> RETRIEVE 1 element @ p = 1... <<--\n" KNRM);
		printf("Element 1 = %d\n", RETRIEVE(1, L_P)->value);

		printf(KGRN "-->> INSERT 5 elements @ p = i... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			INSERT( 4 * i, L_P);
		}

		printf(KGRN "-->> RETRIEVE 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			printf("Element %d = %d\n", i, RETRIEVE(i,L_P)->value);
		}

		display_list(L_P);

		printf("5th value = %d \n", RETRIEVE(5, L_P)->value);

		printf(KGRN "-->> Inserting 45 at position 5... <<-- \n" KNRM);
		INSERT(45, 5, L_P);
		printf("5th value = %d \n", RETRIEVE(5, L_P)->value);
		printf("5th place, previous = %d \n", PREVIOUS(RETRIEVE(5, L_P), L_P)->value);
		printf("5th place, next = %d \n", NEXT(RETRIEVE(5, L_P), L_P)->value);
		printf("END Value  = %d \n", RETRIEVE(PREVIOUS(END(L_P), L_P))->value);
		printf("FIRST Value = %d \n", RETRIEVE(FIRST(L_P))->value);

		display_list(L_P);

		printf(KGRN "-->> Deleting 45 at position 5... <<-- \n" KNRM);
		DELETE(5, L_P);
		printf("5th value = %d \n", RETRIEVE(5, L_P)->value);
		printf("5th place, previous = %d \n", PREVIOUS(RETRIEVE(5, L_P), L_P)->value);
		printf("5th place, next = %d \n", NEXT(RETRIEVE(5, L_P), L_P)->value);
		printf("END Value  = %d \n", RETRIEVE(PREVIOUS(END(L_P), L_P))->value);
		printf("FIRST Value = %d \n", RETRIEVE(FIRST(L_P))->value);

		display_list(L_P);
		display_list_memory(L_P);

		std::cout << KGRN << "-->> Deleting from end... <<-- \n" << KNRM;
		DELETE(PREVIOUS(END(L_P), L_P));
		std::cout << "END() value = " << RETRIEVE(PREVIOUS(END(L_P), L_P))->value << "\n";
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L_P), L_P) << "\n";
		std::cout << "FIRST Value = " << RETRIEVE(FIRST(L_P))->value << "\n";

		display_list(L_P);

		std::cout << KGRN << "-->> Deleting from end... <<-- \n" << KNRM;
		DELETE(PREVIOUS(END(L_P), L_P));
		std::cout << "END() value = " << RETRIEVE(PREVIOUS(END(L_P), L_P), L_P)->value << "\n";
		std::cout << "Position of PREVIOUS(END) = " << PREVIOUS(END(L_P), L_P) << "\n";
		std::cout << "FIRST Value = " << RETRIEVE(FIRST(L_P), L_P)->value << "\n";

		display_list(L_P);

		std::cout << KGRN << "-->> Deleting from first... <<-- \n" << KNRM;
		DELETE(FIRST(L_P));
		std::cout << "FIRST() value = " << RETRIEVE(FIRST(L_P))->value << "\n";
		std::cout << "NEXT(FIRST) = " << RETRIEVE(FIRST(L_P))->value << "\n";
		std::cout << "Position of PREVIOUS(FIRST) = " << PREVIOUS(FIRST(L_P), L_P) << "\n";
		std::cout << "FIRST = " << RETRIEVE(FIRST(L_P))->value << "\n";

		display_list(L_P);

		free_list(L_P);

		} else if (arg1.compare("test_sa") == 0) {

		int i;

		std::cout << KRED << "\n\n\t---- Stack, array implementation ----\n" << KNRM;

		StackArray::stack* S;

		S = (StackArray::stack*) std::malloc(sizeof(StackArray::stack));

		printf(KGRN "-->> MAKENULL... <<--\n" KNRM);
		MAKENULL( S );

		printf(KGRN "-->> PUSH 1 element (Value = 5)... <<--\n" KNRM);
		PUSH(5, S);
		printf("Top = %d\n", TOP(S));

		printf(KGRN "-->> POP element... <<--\n" KNRM);
		POP(S);

		printf(KGRN "-->> PUSH 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			PUSH( 4 * i, S);
		}

		printf(KGRN "-->> TOP then POP 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			printf("Element %d = %d\n", i, TOP(S));
			display_stack(S);
			std::cout << KGRN << "-->> pop...<<--" << KNRM << std::endl;
			POP(S);
			display_stack(S);
		}

		std::free(S);

		} else if (arg1.compare("test_sp") == 0) {

		int i;

		std::cout << KRED << "\n\n\t---- Stack, pointer implementation ----\n" << KNRM;

		StackPointer::stack* S_P = NULL;
		StackPointer::node* q, * temp;

		printf(KGRN "-->> MAKENULL... <<--\n" KNRM);
		S_P = MAKENULL( S_P );

		printf(KGRN "-->> PUSH 1 element... <<--\n" KNRM);
		PUSH(5, S_P);
		printf("Top = %d\n", TOP(S_P)->value);

		printf(KGRN "-->> POP element... <<--\n" KNRM);
		POP(S_P);
		printf("Address of top = %p\n", TOP(S_P));

		printf(KGRN "-->> PUSH 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			PUSH( 4 * i, S_P);
		}

		display_stack(S_P);

		printf(KGRN "-->> TOP then POP 5 elements... <<--\n" KNRM);
		for ( i = 1; i < 6; i++ )
		{
			printf("Element %d = %d\n", i, TOP(S_P)->value);
			printf("Address of top = %p\n", TOP(S_P));
			display_stack(S_P);
			std::cout << KGRN << "-->> pop... <<--" << KNRM << std::endl;
			POP(S_P);
			display_stack(S_P);
		}

		printf(KGRN "-->> PUSH 25 elements... <<--\n" KNRM);
		for ( i = 1; i < 26; i++ )
		{
			PUSH( 2 * i, S_P);
		}

		display_stack(S_P);

		printf(KGRN "-->> POP 25 elements... <<--\n" KNRM);
		for ( i = 1; i < 26; i++ )
		{
			POP(S_P);
		}

		display_stack(S_P);

		q = S_P->top;

		while (q->next != NULL)
		{
			temp = q->next;
			q->next = q->next->next;
			std::free(temp);
		}
		std::free(S_P);

	} else if (arg1.compare("ll") == 0) { // List, library

		std::list<int> L (0,0);
		int i;
		int j;

		unsigned long int insert_end_avg = 0;
		unsigned long int insert_front_avg = 0;
		unsigned long int traverse_avg = 0;
		unsigned long int delete_end_avg = 0;
		unsigned long int delete_front_avg = 0;

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		runs = 10;

		std::cout << KGRN "\n---- List, library implementation ----\n" KNRM;

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				L.push_back(i);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

			insert_end_avg = insert_end_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				L.pop_back();
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

			delete_end_avg = delete_end_avg + elapsed.count();
		}

		insert_end_avg = insert_end_avg / runs;
		delete_end_avg = delete_end_avg / runs;
		std::cout << "Insertion from end average   = " << insert_end_avg  << " ns " << std::endl;
		std::cout << "Deletion from end average    = " << delete_end_avg  << " ns " << std::endl;

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				L.push_front(i);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			insert_front_avg = insert_front_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Traverse

			for (std::list<int>::iterator itter=L.begin(); itter != L.end(); itter++)
			{

			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			traverse_avg = traverse_avg + elapsed.count();

			start = std::chrono::steady_clock::now(); // Delete, front

			for ( i = 1; i <= n; i++ )
			{
				L.pop_front();
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
			delete_front_avg = delete_front_avg + elapsed.count();
		}

		insert_front_avg = insert_front_avg / runs;
		traverse_avg = traverse_avg / runs;
		delete_front_avg = delete_front_avg / runs;
		std::cout << "Insertion from front average = " << insert_front_avg  << " ns " << std::endl;
		std::cout << "Traversal average            = " << traverse_avg  << " ns " << std::endl;
		std::cout << "Deletion from front average  = " << delete_front_avg  << " ns " << std::endl;

		file_out.open(OUTPUT_FILE, std::ios::app);
		file_out << arg1 << "," << n << ",,," << insert_end_avg << "," << insert_front_avg << "," << delete_end_avg << "," << delete_front_avg << "," << traverse_avg << "\n";

		file_out.close();

	} else if (arg1.compare("sl") == 0) { // Stack, library
		int i;
		int j;

		int push_avg = 0;
		int pop_avg = 0;

		auto start = std::chrono::steady_clock::now();
		auto end = std::chrono::steady_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

		std::stack<int> S;

		std::cout << KGRN "\n---- Stack, library implementation ----\n" KNRM;

		for ( j = 1; j <= runs; j++)
		{
			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				S.push(i);
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

			push_avg = push_avg + elapsed.count();

			start = std::chrono::steady_clock::now();

			for ( i = 1; i <= n; i++ )
			{
				S.pop();
			}

			end = std::chrono::steady_clock::now();
			elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

			pop_avg = pop_avg + elapsed.count();
		}

		push_avg = push_avg / runs;
		pop_avg = pop_avg / runs;

		std::cout << "Push average = " << push_avg  << " ns " << std::endl;
		std::cout << "Pop average  = " << pop_avg  << " ns " << std::endl;

		file_out.open(OUTPUT_FILE, std::ios::app);
		file_out << arg1 << "," << n << "," << push_avg << "," << pop_avg << "\n";
		file_out.close();

	}
}


