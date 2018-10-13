/*
 * huffman.cpp
 *
 *  Created on: Aug 14, 2018
 *      Author: Juniper
 */



//#include "lcrstree.cpp"
#include <iostream>

#define MAX_TREES 1000

typedef unsigned int node_ptr;
typedef node_ptr position;

namespace detail
{
	class Tree_Element
	{
	public:
		Tree_Element();
		Tree_Element(node_ptr l, node_ptr r, node_ptr p);
		node_ptr left_child;
		node_ptr right_child;
		node_ptr parent;

	};

	Tree_Element::Tree_Element()
	{
		left_child = 0;
		right_child = 0;
		parent = 0;
	}

	Tree_Element::Tree_Element(node_ptr l, node_ptr r, node_ptr p)
	{
		left_child = l;
		right_child = r;
		parent = p;
	}

	class Trees
	{
	public:
		Trees();
		void add_tree(Tree_Element t);
		Tree_Element elements[MAX_TREES];
		node_ptr node_last;
	};

	Trees::Trees()
	{
		node_last = 0;
	}

	void Trees::add_tree(Tree_Element t)
	{
		node_last++;
		elements[node_last] = t;
	}

	class Forest_Element
	{
	public:
		Forest_Element();
		Forest_Element(int w, node_ptr r);
		int	weight;
		node_ptr root;
	};

	class Forest
	{
	public:
		Forest();
		Trees trees;
		Forest_Element elements[MAX_TREES];
		node_ptr tree_last;

		void add_forest_element(Forest_Element f);
		void lightones(node_ptr* least, node_ptr* second);
		void Huffman();
		node_ptr create(node_ptr tree_left, node_ptr tree_right);

	};

	class Alphabet_element
	{
	public:
		Alphabet_element();
		Alphabet_element(char s, node_ptr p, node_ptr l);
		char symbol;
		int probability;
		node_ptr leaf;
	};

	class Alphabet
	{
	public:
		Alphabet();
		Alphabet_element elements[MAX_TREES];
		void add_alphabet(Alphabet_element a);
		int num_elements;
	};

	Alphabet_element::Alphabet_element()
	{
		symbol = '0';
		probability = 0;
		leaf = 0;
	}

	Alphabet_element::Alphabet_element(char s, node_ptr p, node_ptr l)
	{
		symbol = s;
		probability = p;
		leaf = l;
	}

	Alphabet::Alphabet()
	{
		num_elements = 0;
	}


	void Alphabet::add_alphabet(Alphabet_element a)
	{
		num_elements++;
		elements[num_elements] = a;
	}

	Forest_Element::Forest_Element()
	{
		weight = 0;
		root = 0;
	}

	Forest_Element::Forest_Element(int w, node_ptr r)
	{
		weight = w;
		root = r;
	}

	void Forest::add_forest_element(Forest_Element f)
	{
		tree_last++;
		elements[tree_last] = f;
	}

	Forest::Forest()
	{
		trees = Trees();
		tree_last = 0;
	}

	void Forest::lightones(node_ptr* least, node_ptr* second)
	{
		unsigned int i;

		if (elements[1].weight <= elements[2].weight)
		{
			*least = 1;
			*second = 2;
		} else {
			*least = 2;
			*second = 1;
		}

		for (i = 3; i <= tree_last; i++)
		{
			if (elements[i].weight < elements[*least].weight)
			{
				*second = *least;
				*least = i;
			} else if (elements[i].weight < elements[*second].weight) {
				*second = i;
			}
		}

	}

	node_ptr Forest::create(node_ptr tree_left, node_ptr tree_right)
	{
		trees.node_last++;

		trees.elements[trees.node_last].left_child = elements[tree_left].root;
		trees.elements[trees.node_last].right_child = elements[tree_right].root;
		trees.elements[trees.node_last].parent = 0;

		trees.elements[elements[tree_left].root].parent = trees.node_last;
		trees.elements[elements[tree_right].root].parent = trees.node_last;

		return trees.node_last;
	}

	void Forest::Huffman()
	{
		node_ptr i, j;
		node_ptr new_root;

		while (tree_last > 1)
		{
			lightones(&i, &j);
			new_root = create(i, j);

			elements[i].weight = elements[i].weight + elements[j].weight;

			elements[i].root = new_root;
			elements[j] = elements[tree_last];

			tree_last = tree_last - 1;
		}
	}

	void print_forest(Forest f)
	{
		unsigned int i;

		std::cout << "\n --- Forest Listings ---\n"
				  << " ------------------------------------------------ \n"
				  << "| Entry \t | Weight \t | Root \t | \n"
				  << " ------------------------------------------------ \n";

		for (i = 1; i <= f.tree_last; i++)
		{
			std::cout << "|\t " << i << "\t | \t"
					<< f.elements[i].weight << "\t | \t"
					<< f.elements[i].root << "\t | \n";
		}

		std::cout << " ------------------------------------------------ \n";
	}

	void print_alphabet(Alphabet a)
	{
		int i;

		std::cout << "\n --- Alphabet Listings ---\n"
				  << " ---------------------------------------------------------------- \n"
				  << "| Entry \t | Symbol \t | Probability \t | Leaf \t | \n"
				  << " ---------------------------------------------------------------- \n";

		for (i = 1; i <= a.num_elements; i++)
		{
			std::cout << "|\t " << i << "\t | \t"
					<< a.elements[i].symbol << "\t | \t"
					<< a.elements[i].probability << "\t | \t"
					<< a.elements[i].leaf << "\t | \n";
		}

		std::cout << " ---------------------------------------------------------------- \n";
	}

	void print_trees(Trees t)
	{
		unsigned int i;

		std::cout << "\n --- Tree Listings ---\n"
				<< " ---------------------------------------------------------------- \n"
				  << "| Entry \t | Left Child \t | Right Child \t | Parent \t | \n"
				  << " ---------------------------------------------------------------- \n";

		for (i = 1; i <= t.node_last; i++)
		{
			std::cout << "|\t "<< i << "\t | \t"
					<< t.elements[i].left_child << "\t | \t"
					<< t.elements[i].right_child << "\t | \t"
					<< t.elements[i].parent << "\t | \n";
		}

		std::cout << " ---------------------------------------------------------------- \n";
	}

}

int main(int argc, char** argv)
{
	detail::Alphabet ALPHABET;
	detail::Forest FOREST;
	detail::Tree_Element null_tree = detail::Tree_Element(0, 0, 0);

	int i;

	for (i = 0; i < 5; i++)
	{
		FOREST.trees.add_tree(null_tree);
	}

	ALPHABET.add_alphabet(detail::Alphabet_element('a', 12, 1));
	ALPHABET.add_alphabet(detail::Alphabet_element('b', 40, 2));
	ALPHABET.add_alphabet(detail::Alphabet_element('c', 15, 3));
	ALPHABET.add_alphabet(detail::Alphabet_element('d', 8, 4));
	ALPHABET.add_alphabet(detail::Alphabet_element('e', 25, 5));

	FOREST.add_forest_element(detail::Forest_Element(12, 1));
	FOREST.add_forest_element(detail::Forest_Element(40, 2));
	FOREST.add_forest_element(detail::Forest_Element(15, 3));
	FOREST.add_forest_element(detail::Forest_Element(8, 4));
	FOREST.add_forest_element(detail::Forest_Element(25, 5));

	std::cout << "\n----------------------------"
			  << "\n>> Initialized Structures <<"
			  << "\n----------------------------\n";

	detail::print_forest(FOREST);
	detail::print_alphabet(ALPHABET);
	detail::print_trees(FOREST.trees);

	FOREST.Huffman();

	std::cout << "\n--------------------------------"
			  << "\n>> Structures After Huffman() <<"
			  << "\n--------------------------------\n";

	detail::print_forest(FOREST);
	detail::print_alphabet(ALPHABET);
	detail::print_trees(FOREST.trees);
}



