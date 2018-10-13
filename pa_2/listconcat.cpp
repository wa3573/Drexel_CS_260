/*
 * listconcat.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: Juniper
 */

#include "list.cpp"


/* Note: the computational complexity of this solution is O(n^2)
 * this is a result of the requirement that we only use the basic list ops,
 * A better approach would be the so called, "divide and conquer" method
 * which utilizes recursion and direct manipulation of list nodes and
 * their "next" field, specifically.
 *
 * Also, I have re-implemented this List::List class as a template,
 * allowing any data type to be stored inside the nodes, the function names
 * are not identical (e.g. init() instead of MAKENULL()) but each has its
 * counterpart, and the core implementation details are the same.
 */

template<typename T>
List::List<T>* list_concatenate(List::List<List::List<T>*>* l_l)
{
	List::List<T>* new_list = new List::List<T>;
	List::List<T>* li_1;
	List::node<List::List<T>*>* p1;	// pointer to a node in the list of lists
	List::node<T>* p2;				// pointer to a node in a given list

	p1 = l_l->front();				// initialize to first list

	// Traverse list of lists
	while (l_l->next(p1) != NULL)
	{
		li_1 = p1->data;			// get list for this iteration
		p2 = li_1->front();			// pointer to front of that list

		// Traverse iteration's list
		while (li_1->next(p2) != NULL)
		{
			new_list->push_back(p2->data);	// add element to new_list
			p2 = li_1->next(p2);			// increment list pointer
		}

		p1 = l_l->next(p1);			// increment list of lists pointer
	}

	return new_list;
}

void problem_24()
{
	List::List<int>* li_1 = new List::List<int>;
	List::List<int>* li_2 = new List::List<int>;
	List::List<int>* li_3 = new List::List<int>;
	List::List<List::List<int>*>* li_4 = new List::List<List::List<int>*>;
	List::List<int>* li_5 = new List::List<int>;
	int i;

	for (i = 1; i < 6; i++)
	{
		li_1->push_back(i);
		li_2->push_back(i + 5);
		li_3->push_back(i + 10);
	}

	std::cout << "\nGiven lists:\n";

	List::display_list(li_1);
	List::display_list(li_2);
	List::display_list(li_3);

	li_4->push_back(li_1);
	li_4->push_back(li_2);
	li_4->push_back(li_3);

	li_5 = list_concatenate(li_4);

	std::cout << "\nConcatenated lists:\n";

	List::display_list(li_5);
}

int main(int argc, char** argv)
{
	problem_24();
}
