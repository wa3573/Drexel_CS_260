/*
 * main.cpp
 *
 *
 *      CSV output: implementation, n, taverse_pre_avg, taverse_pre_avg
 *
 *      The timing implementation is almost exactly the same as in PA 1,
 *      Note: I have not bothered to delete allocated memory (pointers)
 *      but am reasonably sure there will be minimal memory leakage, and thus
 *      we can rely upon the system to clean up afterwards. I have implemented
 *      functions to do so, if desired. However, time did not allow for me to
 *      put them to use in the code.
 *
 *
 *  Created on: Jul 31, 2018
 *      Author: Juniper
 */

#include <iostream>
////#include <cstring>
#include <string>
//#include <cstdint>
//#include <initializer_list>s
#include <assert.h>
#include <chrono>
//#include <list>
#include <fstream>
#include <algorithm>

#include <stdlib.h>

#include "lcrstree.cpp"
#include "loctree.cpp"
#include "pointerqueue.cpp"
//#include "list.cpp"
//#include "tree_lcrs.cpp"
#include "style.h"

#define OUTPUT_FILE "out.csv"

int count = 0; 	// for traverse debug
static volatile bool VERBOSE = false;
static volatile int n;
static volatile int runs = 100;


/* Instantiate cursor space for the LCRS implementation:
 * This allows all the objects to share the same CURSOR_SPACE variable
 * without loosing the benefits of object orientation. This is necessary
 * to ensure proper functionality of CREATEn() since the algorithm used
 * relies upon this shared cursor space. In the future I would most-likely
 * create a CursorSpace object which would contain the trees as members.
 */
namespace TreeLCRS_cur
{
	template<typename T>
	node<T> CURSOR_SPACE[T_LCRS_CUR_SPACE_SIZE];

	bool CURSOR_SPACE_INITIALIZED = false;
	node_ptr avail;
}

template<typename T>
void t_traverse_pre_LOC(TreeLOC::Tree<T>* t, TreeLOC::node<T>* n)
{
	TreeLOC::node<T>* c;

	/* Code here for preorder ops */
	if (VERBOSE)
	{
		std::cout << t->LABEL(n)->value << ", ";
	}
	c = t->LEFTMOST_CHILD(n);

	while (c != NULL)
	{
		t_traverse_pre_LOC(t, c);
		c = t->RIGHT_SIBLING(c);
	}


}

template<typename T>
void t_traverse_post_LOC(TreeLOC::Tree<T>* t, TreeLOC::node<T>* n)
{
	TreeLOC::node<T>* c;

	c = t->LEFTMOST_CHILD(n);

	while (c != NULL)
	{
		t_traverse_post_LOC(t, c);
		c = t->RIGHT_SIBLING(c);
	}

	/* Code here for postorder ops */
	if (VERBOSE)
	{
		std::cout << t->LABEL(n)->value << ", ";
	}


}

template<typename T>
void t_traverse_pre_LCRS_cur(TreeLCRS_cur::Tree<T> t, TreeLCRS_cur::node<T> n)
{
	TreeLCRS_cur::node<T> c;
	TreeLCRS_cur::node<T> last;

	/* Code here for preorder ops */
	if (VERBOSE)
	{
		std::cout << t.LABEL(n).value << ", ";
	}

	c = t.LEFTMOST_CHILD(n);

	last = c;
	while (last.right_sib != 0)
	{
		last = c;
		t_traverse_pre_LCRS_cur(t, c);
		c = t.RIGHT_SIBLING(c);
	}
}

template<typename T>
void t_traverse_post_LCRS_cur(TreeLCRS_cur::Tree<T> t, TreeLCRS_cur::node<T> n)
{
	TreeLCRS_cur::node<T> c;
	TreeLCRS_cur::node<T> last;

	c = t.LEFTMOST_CHILD(n);

	last = c;
	while (last.right_sib != 0)
	{
		last = c;
		t_traverse_post_LCRS_cur(t, c);
		c = t.RIGHT_SIBLING(c);
	}

	/* Code here for postorder ops */
	if (VERBOSE)
	{
		std::cout << t.LABEL(n).value << ", ";
	}

}


void test_queue()
{
	std::cout << "\n\t========== Queue, tests ========== \n\n";

	Queue::Queue<int>* Q = new Queue::Queue<int>;

	std::cout << T_C_GRN << "-->> ENQUEUE(5)... <<--" << T_RESET << std::endl;
	Q->ENQUEUE(5);
	std::cout << "Front = " << Q->FRONT()->value << std::endl;
	std::cout << "Back = " << Q->BACK()->value << std::endl;
	assert(Q->FRONT()->value == 5);
	std::cout << "(Front == 5) == true\n";
	assert(Q->FRONT()->value == Q->BACK()->value);
	std::cout << "(Front == Back) == true\n";

	std::cout << T_C_GRN << "-->> ENQUEUE(10)... <<--" << T_RESET << std::endl;
	Q->ENQUEUE(10);
	std::cout << "Front = " << Q->FRONT()->value << std::endl;
	std::cout << "Back = " << Q->BACK()->value << std::endl;
	assert(Q->FRONT()->value == 5);
	std::cout << "(Front == 5) == true\n";
	assert(Q->BACK()->value == 10);
	std::cout << "(Back == 10) == true\n";

	std::cout << T_C_GRN << "-->> DEQUEUE()... <<--" << T_RESET << std::endl;
	Q->DEQUEUE();
	std::cout << "Front = " << Q->FRONT()->value << std::endl;
	std::cout << "Back = " << Q->BACK()->value << std::endl;
	assert(Q->FRONT()->value == 10);
	std::cout << "(Front == 10) == true\n";
	assert(Q->FRONT()->value == Q->BACK()->value);
	std::cout << "(Front == Back) == true\n";
}

void test_tree_loc()
{
		/* ---- Tree: LOC ---- */

	std::cout << "\n\t========== Tree: LoC, tests ========== \n\n";

	std::cout << "\tTree to be constructed: \n"
			  << "\n     [    I    ]"
			  << "\n    /           \\"
			  << "\n   G             H"
			  << "\n /   \\        /  |  \\"
			  << "\nA     B	     C   D   E \n\n";

	TreeLOC::label* label3 = new TreeLOC::label("A");
	TreeLOC::Tree<int>* T15 = new TreeLOC::Tree<int>(label3);
	label3 = new TreeLOC::label("B");
	TreeLOC::Tree<int>* T16 = new TreeLOC::Tree<int>(label3);
	label3 = new TreeLOC::label("C");
	TreeLOC::Tree<int>* T17 = new TreeLOC::Tree<int>(label3);
	label3 = new TreeLOC::label("D");
	TreeLOC::Tree<int>* T18 = new TreeLOC::Tree<int>(label3);
	label3 = new TreeLOC::label("E");
	TreeLOC::Tree<int>* T19 = new TreeLOC::Tree<int>(label3);
	TreeLOC::Tree<int>* T21;
	TreeLOC::Tree<int>* T22;
	TreeLOC::Tree<int>* T23;

	label3 = new TreeLOC::label("G");
	T21 = TreeLOC::CREATE2(label3, T15, T16);
	label3 = new TreeLOC::label("H");
	T22 = TreeLOC::CREATE3(label3, T17, T18, T19);
	label3 = new TreeLOC::label("I");
	T23 = TreeLOC::CREATE2(label3, T21, T22);

	List::List<TreeLOC::Tree<int>*>* list_trees_loc = new List::List<TreeLOC::Tree<int>*>; // List of pointers to free memory after

	list_trees_loc->push_back(T15);
	list_trees_loc->push_back(T16);
	list_trees_loc->push_back(T17);
	list_trees_loc->push_back(T18);
	list_trees_loc->push_back(T19);
	list_trees_loc->push_back(T21);
	list_trees_loc->push_back(T22);
	list_trees_loc->push_back(T23);

	std::cout << "\n\t========== Tree: LOC, assert, using basic ADT ops, multiple-syntaxes ========== \n";
	assert((T23->ROOT()->label->value).compare("I") == 0);
	std::cout << "Label I in correct position \n";
	assert((T23->LEFTMOST_CHILD()->label->value).compare("G") == 0);
	std::cout << "Label G in correct position \n";
	assert((T23->LEFTMOST_CHILD()->RIGHT_SIBLING()->label->value).compare("H") == 0);
	std::cout << "Label H in correct position \n";
	assert((T23->LEFTMOST_CHILD()->LEFTMOST_CHILD()->label->value).compare("A") == 0);
	assert((T23->LEFTMOST_CHILD(T23->LEFTMOST_CHILD())->label->value).compare("A") == 0);
	std::cout << "Label A in correct position \n";
	assert((T23->LEFTMOST_CHILD()->LEFTMOST_CHILD()->RIGHT_SIBLING()->label->value).compare("B") == 0);
	assert((T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD(T23->LEFTMOST_CHILD()))->label->value).compare("B") == 0);
	std::cout << "Label B in correct position \n";
	assert((T23->LEFTMOST_CHILD()->RIGHT_SIBLING()->LEFTMOST_CHILD()->label->value).compare("C") == 0);
	assert((T23->LEFTMOST_CHILD(T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD()))->label->value).compare("C") == 0);
	std::cout << "Label C in correct position \n";
	assert((T23->LEFTMOST_CHILD()->RIGHT_SIBLING()->LEFTMOST_CHILD()->RIGHT_SIBLING()->label->value).compare("D") == 0);
	assert((T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD(T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD())))->label->value).compare("D") == 0);
	std::cout << "Label D in correct position \n";
	assert((T23->LEFTMOST_CHILD()->RIGHT_SIBLING()->LEFTMOST_CHILD()->RIGHT_SIBLING()->RIGHT_SIBLING()->label->value).compare("E") == 0);
	assert((T23->RIGHT_SIBLING(T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD(T23->RIGHT_SIBLING(T23->LEFTMOST_CHILD()))))->label->value).compare("E") == 0);
	std::cout << "Label E in correct position \n";

}

void test_tree_lcrs_cur()
{

	std::cout << "\n\t========== Tree: LCRS, cursor, tests ========== \n\n";

	std::cout << "\tTree to be constructed: \n"
			  << "\n     [    I    ]"
			  << "\n    /           \\"
			  << "\n   G             H"
			  << "\n /   \\        /  |  \\"
			  << "\nA     B	     C   D   E \n\n";


	TreeLCRS_cur::label label32;

	std::strcpy(label32.value, "A");
	TreeLCRS_cur::Tree<int> T30 = TreeLCRS_cur::CREATE0<int>(label32);
	std::strcpy(label32.value, "B");
	TreeLCRS_cur::Tree<int> T31 = TreeLCRS_cur::CREATE0<int>(label32);
	std::strcpy(label32.value, "C");
	TreeLCRS_cur::Tree<int> T32 = TreeLCRS_cur::CREATE0<int>(label32);
	std::strcpy(label32.value, "D");
	TreeLCRS_cur::Tree<int> T33 = TreeLCRS_cur::CREATE0<int>(label32);
	std::strcpy(label32.value, "E");
	TreeLCRS_cur::Tree<int> T34 = TreeLCRS_cur::CREATE0<int>(label32);

	assert(std::strcmp(T30.LABEL(T30.ROOT()).value, "A") == 0);
	std::cout << "Tree Label == 'A' \n";
	assert(std::strcmp(T32.LABEL(T32.ROOT()).value, "C") == 0);
	std::cout << "Tree Label == 'C' \n";
	assert(std::strcmp(T34.LABEL(T34.ROOT()).value, "E") == 0);
	std::cout << "Tree Label == 'E' \n";

	std::strcpy(label32.value, "G");
	TreeLCRS_cur::Tree<int> T36 = TreeLCRS_cur::CREATE2(label32, T30, T31);

	std::strcpy(label32.value, "H");
	TreeLCRS_cur::Tree<int> T37 = TreeLCRS_cur::CREATE3(label32, T32, T33, T34);

	std::strcpy(label32.value, "I");
	TreeLCRS_cur::Tree<int> T38 = TreeLCRS_cur::CREATE2(label32, T36, T37);

	std::cout << "\n\t========== Tree: LCRS, Cursor implementation, assert, using basic ADT ops ========== \n";
	assert(std::strcmp(T38.LABEL(T38.ROOT()).value, "I") == 0);
	std::cout << "Label I in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD(T38.ROOT())).value, "G") == 0);
	std::cout << "Label G in correct position \n";
//		std::cout << "Label H = " << T38.LABEL(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD(T38.ROOT()))).value << std::endl;
	assert(std::strcmp(T38.LABEL(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD(T38.ROOT()))).value, "H") == 0);
	std::cout << "Label H in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD(T38.LEFTMOST_CHILD())).value, "A") == 0);
	std::cout << "Label A in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD().LEFTMOST_CHILD().RIGHT_SIBLING()).value, "B") == 0);
	assert(std::strcmp(T38.LABEL(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD(T38.LEFTMOST_CHILD()))).value, "B") == 0);
	std::cout << "Label B in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD().RIGHT_SIBLING().LEFTMOST_CHILD()).value, "C") == 0);
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD()))).value, "C") == 0);
	std::cout << "Label C in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD().RIGHT_SIBLING().LEFTMOST_CHILD().RIGHT_SIBLING()).value, "D") == 0);
	assert(std::strcmp(T38.LABEL(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD())))).value, "D") == 0);
	std::cout << "Label D in correct position \n";
	assert(std::strcmp(T38.LABEL(T38.LEFTMOST_CHILD().RIGHT_SIBLING().LEFTMOST_CHILD().RIGHT_SIBLING().RIGHT_SIBLING()).value, "E") == 0);
	assert(std::strcmp(T38.LABEL(T38.RIGHT_SIBLING(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD(T38.RIGHT_SIBLING(T38.LEFTMOST_CHILD()))))).value, "E") == 0);
	std::cout << "Label E in correct position \n";
}

void time_tree_loc()
{
	auto t_start = std::chrono::steady_clock::now();
	auto t_end = std::chrono::steady_clock::now();
	auto t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
	std::ofstream file_out;

	int j, k;
	unsigned long int traverse_pre_avg = 0;
	unsigned long int traverse_post_avg = 0;

	int num_iter = ((double)n / 2) - 1;

	TreeLOC::label* label4 = new TreeLOC::label("1");
	TreeLOC::label* label5 = new TreeLOC::label("2");
	TreeLOC::label* label6 = new TreeLOC::label("3");
	TreeLOC::label* label_temp;

//		TreeLOC::Tree<int>* T15 = TreeLOC::CREATE0<int>(label4);
	TreeLOC::Tree<int>* t_t_11 = new TreeLOC::Tree<int> (label4);
	TreeLOC::Tree<int>* t_t_12 = new TreeLOC::Tree<int> (label4);
	TreeLOC::Tree<int>* t_t_13 = new TreeLOC::Tree<int> (label4);
	TreeLOC::Tree<int>* t_t_2;
	TreeLOC::Tree<int>* t_t_3;
	TreeLOC::Tree<int>* t_t_final;

	std::cout << "Generating full tree with " << n << " levels... \n";


	/* n = 1 */
	if (n == 1)
	{
		/* nothing to do */
	/* n = 2 */
	} else if (n == 2) {
		t_t_final = TreeLOC::CREATE3(label5, t_t_11, t_t_12, t_t_13);
	/* n = 3 */
	} else if (n == 3) {
		t_t_2 = TreeLOC::CREATE3(label5, t_t_11, t_t_12, t_t_13);
		t_t_final = TreeLOC::CREATE3(label6, t_t_2, t_t_2, t_t_2);
	/* general case */
	} else {
		if (VERBOSE)
		{
			std::cout << "Creating tree with root: " << label5->value
					  << ", child 1: " << t_t_11->ROOT()->LABEL()
					  << ", child 2: " << t_t_12->ROOT()->LABEL()
					  << ", child 3: " << t_t_13->ROOT()->LABEL() << std::endl;
		}

		t_t_2 = TreeLOC::CREATE3(label5, t_t_11, t_t_12, t_t_13);

		if (VERBOSE)
		{
			std::cout << "Creating tree with root: " << label6->value
					  << ", child 1: " << t_t_2->ROOT()->LABEL()
					  << ", child 2: " << t_t_2->ROOT()->LABEL()
					  << ", child 3: " << t_t_2->ROOT()->LABEL() << std::endl;
		}

		t_t_3 = TreeLOC::CREATE3(label6, t_t_2, t_t_2, t_t_2);

		int num_level = 4;
		std::string str_num_level;
		for (k = 0; k < num_iter; k++)
		{


			str_num_level = std::to_string(num_level);
			label_temp = new TreeLOC::label(str_num_level);

			if (VERBOSE)
			{
				std::cout << "Creating tree with root: " << label_temp->value
						  << ", child 1: " << t_t_3->ROOT()
						  << ", child 2: " << t_t_3->ROOT()
						  << ", child 3: " << t_t_3->ROOT() << std::endl;
			}

			t_t_2 = TreeLOC::CREATE3(label_temp, t_t_3, t_t_3, t_t_3);
			num_level++;


			str_num_level = std::to_string(num_level);
			label_temp = new TreeLOC::label(str_num_level);

			if (VERBOSE)
			{
				std::cout << "Creating tree with root: " << label_temp->value
						  << ", child 1: " << t_t_2->ROOT()
						  << ", child 2: " << t_t_2->ROOT()
						  << ", child 3: " << t_t_2->ROOT() << std::endl;
			}

			t_t_3 = TreeLOC::CREATE3(label_temp, t_t_2, t_t_2, t_t_2);
			num_level++;
		}

		if (n % 2 == 0)	// if n is even
		{
			t_t_final = t_t_2;
		} else {		// if n is odd
			t_t_final = t_t_3;
		}
	}

	for (j = 1; j <= runs; j++)
	{
		t_start = std::chrono::steady_clock::now(); // Traverse

		t_traverse_pre_LOC(t_t_final, t_t_final->ROOT());
		if (VERBOSE)
			std::cout << std::endl;

		t_end = std::chrono::steady_clock::now();
		t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
		traverse_pre_avg = traverse_pre_avg + t_elapsed.count();
	}

	traverse_pre_avg = traverse_pre_avg / runs;
	std::cout << "Traversal average, preorder = " << traverse_pre_avg  << " ns " << std::endl;

	for (j = 1; j <= runs; j++)
	{
		t_start = std::chrono::steady_clock::now(); // Traverse

		t_traverse_post_LOC(t_t_final, t_t_final->ROOT());
		if (VERBOSE)
			std::cout << std::endl;

		t_end = std::chrono::steady_clock::now();
		t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
		traverse_post_avg = traverse_post_avg + t_elapsed.count();
	}

	traverse_post_avg = traverse_post_avg / runs;
	std::cout << "Traversal average, postorder = " << traverse_post_avg  << " ns " << std::endl;


	file_out.open(OUTPUT_FILE, std::ios::app);

	file_out << "LOC," << n << "," << traverse_pre_avg << "," << traverse_post_avg << "\n";

	file_out.close();
}



void time_tree_lcrs_cur()
{
	auto t_start = std::chrono::steady_clock::now();
	auto t_end = std::chrono::steady_clock::now();
	auto t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
	std::ofstream file_out;

	int j, k;
	unsigned long int traverse_pre_avg = 0;
	unsigned long int traverse_post_avg = 0;

	int num_iter = ((double)n / 2) - 1;

	TreeLCRS_cur::label label4;
	std::strcpy(label4.value, "1");

	TreeLCRS_cur::Tree<int> t_t_1 = TreeLCRS_cur::CREATE0<int>(label4);
	TreeLCRS_cur::Tree<int> t_t_2 = TreeLCRS_cur::Tree<int>();
	TreeLCRS_cur::Tree<int> t_t_3 = TreeLCRS_cur::Tree<int>();
	TreeLCRS_cur::Tree<int> t_t_final = TreeLCRS_cur::Tree<int>();

	std::cout << "Generating full tree with " << n << " levels... \n";


	/* n = 1 */
	if (n == 1)
	{
		/* nothing to do */
	/* n = 2 */
	} else if (n == 2) {
		std::strcpy(label4.value, "2");
		t_t_final = TreeLCRS_cur::CREATE3(label4, t_t_1, t_t_1, t_t_1);
	/* n = 3 */
	} else if (n == 3) {
		std::strcpy(label4.value, "2");
		t_t_2 = TreeLCRS_cur::CREATE3(label4, t_t_1, t_t_1, t_t_1);
		std::strcpy(label4.value, "3");
		t_t_final = TreeLCRS_cur::CREATE3(label4, t_t_2, t_t_2, t_t_2);
	/* general case */
	} else {
		std::strcpy(label4.value, "2");
		t_t_2 = TreeLCRS_cur::CREATE3(label4, t_t_1, t_t_1, t_t_1);
		std::strcpy(label4.value, "3");
		t_t_3 = TreeLCRS_cur::CREATE3(label4, t_t_2, t_t_2, t_t_2);

		int num_level = 4;
		char str_num_level[32];
		for (k = 0; k < num_iter; k++)
		{
			std::sprintf(str_num_level, "%d", num_level);
			std::strcpy(label4.value, str_num_level);
			t_t_2 = TreeLCRS_cur::CREATE3(label4, t_t_3, t_t_3, t_t_3);
			num_level++;
			std::sprintf(str_num_level, "%d", num_level);
			std::strcpy(label4.value, str_num_level);
			t_t_3 = TreeLCRS_cur::CREATE3(label4, t_t_2, t_t_2, t_t_2);
			num_level++;
		}

		if (n % 2 == 0)	// if n is even
		{
			t_t_final = t_t_2;
		} else {		// if n is odd
			t_t_final = t_t_3;
		}
	}

	for (j = 1; j <= runs; j++)
	{
		t_start = std::chrono::steady_clock::now(); // Traverse

		t_traverse_pre_LCRS_cur(t_t_final, t_t_final.ROOT());
		if (VERBOSE)
			std::cout << std::endl;

		t_end = std::chrono::steady_clock::now();
		t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
		traverse_pre_avg = traverse_pre_avg + t_elapsed.count();
	}

	traverse_pre_avg = traverse_pre_avg / runs;
	std::cout << "Traversal average, preorder = " << traverse_pre_avg  << " ns " << std::endl;

	for (j = 1; j <= runs; j++)
	{
		t_start = std::chrono::steady_clock::now(); // Traverse

		t_traverse_post_LCRS_cur(t_t_final, t_t_final.ROOT());
		if (VERBOSE)
			std::cout << std::endl;

		t_end = std::chrono::steady_clock::now();
		t_elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(t_end - t_start);
		traverse_post_avg = traverse_post_avg + t_elapsed.count();
	}

	traverse_post_avg = traverse_post_avg / runs;
	std::cout << "Traversal average, postorder = " << traverse_post_avg  << " ns " << std::endl;

	file_out.open(OUTPUT_FILE, std::ios::app);

	file_out << "LCRS," << n << "," << traverse_pre_avg << "," << traverse_post_avg << "\n";

	file_out.close();
}

int main(int argc, char** argv)
{
	std::string::size_type size_string;
	std::string arg1, arg2;


	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << "<action> <# of tree levels>" << std::endl;
		exit(EXIT_SUCCESS);
	} else if (argc == 2) {
		arg1 = (std::string) argv[1];
	} else if (argc == 3)
	{
		arg1 = (std::string) argv[1];
		arg2 = (std::string) argv[2];
		n = std::stoi(arg2, &size_string, 10);
	} else {
		std::cout << "Usage: " << argv[0] << "<action> <# of tree levels>" << std::endl;
		exit(EXIT_SUCCESS);
	}

	std::cout << "Arg 1: " << arg1 << std::endl;

	if (arg1.compare("test_queue") == 0)
	{
		test_queue();

	} else if (arg1.compare("test_tree_loc") == 0) {
		test_tree_loc();

	} else if (arg1.compare("test_tree_lcrs") == 0) {
		test_tree_lcrs_cur();

	} else if (arg1.compare("time_tree_loc") == 0) {
		time_tree_loc();

	} else if (arg1.compare("time_tree_lcrs") == 0) {
		time_tree_lcrs_cur();

	}

	std::exit(EXIT_SUCCESS);
}
