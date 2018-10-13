/*
 * merge_lists.cpp
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
List::List<T>* merge_sorted(List::List<T>* arr[], int n)
{
	List::List<T>* res = new List::List<T>;
	List::node<T>* p1;
	List::node<T>* p2;

	int i;

	// Initialize result to first list
	res = arr[0];

	// For each of the other lists
	for (i = 1; i < n; i++)
	{
		// Set pointers to first node of result and this iteration's list
		p1 = res->front();
		p2 = arr[i]->front();

		// Traverse this iteration's list
		while (arr[i]->next(p2) != NULL)
		{
			/* For each element of this iteration's list, find the index
			 * to insert in the result using traversal of the result list
			 */
			while (p1 != res->back() && p2->data > res->next(p1)->data)
			{
				p1 = res->next(p1);
			}

			// Insert node in question at the determined position
			res->insert(p2->data, p1);
			// Move to next position in iteration's list
			p2 = arr[i]->next(p2);
		}
	}

	return res;
}

void problem_23b()
{
	List::List<int>* li_1 = new List::List<int>;
	List::List<int>* li_2 = new List::List<int>;
	List::List<int>* li_3 = new List::List<int>;
	List::List<int>* li_4 = new List::List<int>;
	List::List<int>* li_5 = new List::List<int>;
	List::List<int>* li_7;
	List::List<int>* arr[10];
	int i;

	for (i = 1; i < 20; i = i + 5)
	{
		li_1->push_back(i);
		li_2->push_back(i + 1);
		li_3->push_back(i + 2);
		li_4->push_back(i + 3);
		li_5->push_back(i + 4);
	}

	std::cout << "\nGiven lists:\n";

	List::display_list(li_1);
	List::display_list(li_2);
	List::display_list(li_3);
	List::display_list(li_4);
	List::display_list(li_5);

	arr[0] = li_1;
	arr[2] = li_2;
	arr[1] = li_3;
	arr[3] = li_4;
	arr[4] = li_5;

//		li_7 = merge_n_lists(arr, 3);
	li_7 = merge_sorted(arr, 5);

	std::cout << "\nMerged lists:\n";

	List::display_list(li_7);
}

int main(int argc, char** argv)
{
	problem_23b();
}
