/*
 * levelorder.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: Juniper
 */




#include "loctree.cpp"
//#include "list.cpp"
#include "pointerqueue.cpp"



template<typename T>
void print_levels(TreeLOC::Tree<T>* t)
{
	TreeLOC::node<T>* c1;
	TreeLOC::node<T>* c2;

	Queue::Queue<TreeLOC::node<T>*>* visited_nodes = new Queue::Queue<TreeLOC::node<T>*>;

	// Initialize queue with Root, and then NULL, to indicate the next level
	visited_nodes->ENQUEUE(t->ROOT());
	visited_nodes->ENQUEUE(NULL);

	int it = 0;

	// Until only the root of the tree remains in the queue
	while (visited_nodes->logical_length > 1)
	{
		it++;
		if (it > 25) // Safety check
			break;

		c1 = visited_nodes->FRONT()->value;
		visited_nodes->DEQUEUE();

		if (c1 == NULL)
		{
			// Reached the next level, print new line and re-enqueue NULL
			visited_nodes->ENQUEUE(NULL);
			std::cout << std::endl;

		} else {

			if (c1->LEFTMOST_CHILD() != NULL)
			{

				c2 = c1->LEFTMOST_CHILD();

				while (c2 != NULL)
				{
					visited_nodes->ENQUEUE(c2);
					c2 = c2->RIGHT_SIBLING();
				}

			}

			std::cout << c1->label->value;

		}
	}

}


void problem_310()
{
	std::cout << "\n\t========== Problem 3.10 ========== \n\n";

	std::cout << "\tInput tree: \n"
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
//	label3 = new TreeLOC::label("F");
	TreeLOC::Tree<int>* T21;
	TreeLOC::Tree<int>* T22;
	TreeLOC::Tree<int>* T23;

	label3 = new TreeLOC::label("G");
	T21 = TreeLOC::CREATE2(label3, T15, T16); // @suppress("Invalid arguments")
	label3 = new TreeLOC::label("H");
	T22 = TreeLOC::CREATE3(label3, T17, T18, T19); // @suppress("Invalid arguments")
	label3 = new TreeLOC::label("I");
	T23 = TreeLOC::CREATE2(label3, T21, T22); // @suppress("Invalid arguments")

	std::cout << "\tprint_levels() output: \n";
	print_levels(T23);

}

int main(int argc, char** argv)
{
	problem_310();
}

