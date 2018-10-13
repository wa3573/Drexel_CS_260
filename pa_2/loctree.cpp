/*
 * tree_loc.cpp
 *
 *  Created on: Jul 31, 2018
 *      Author: Juniper
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <initializer_list>
#include <string>

#include "list.cpp"

#define MAX_NODES 1000

namespace TreeLOC
{
	template<typename T>
	class Tree;

	/* label has been implemented as a structure to allow for ease of future
	 * changes/augmentations. Currently just holds a string as member "value"
	 */
	struct label {
		std::string value;
		label() {
			value.assign("");
		};


		label(std::string in)
		{
			value.assign(in);
		};
	};

	// Node object with utility functions
	template<typename T>
	struct node {
		T 						value;
		node<T>*				parent;
		List::List<node<T>*>*	children;
		TreeLOC::label* 		label;
		void					set_value(T in);
		node<T>*				RIGHT_SIBLING();
		node<T>*				LEFTMOST_CHILD();
		TreeLOC::label* 		LABEL();
	};

	template<typename T>
	void node<T>::set_value(T in)
	{
		value = in;
	}

	template<typename T>
	label* node<T>::LABEL()
	{
		return label;
	}

	template<typename T>
	node<T>* node<T>::LEFTMOST_CHILD()
	{
		node<T>* target;
		Tree<T> temp; // Temp tree as dummy argument

		target = temp.LEFTMOST_CHILD(this);
		return target;
	}


	template<typename T>
	node<T>* node<T>::RIGHT_SIBLING()
	{
		node<T>* target;
		Tree<T> temp; // Temp tree as dummy argument

		target = temp.RIGHT_SIBLING(this);
		return target;
	}

	template<typename T>
	class Tree
	{
		node<T>*	root;
		void		free_node(node<T>* n);
	public:
					Tree();
					~Tree() { destroy(); }
					Tree(label* lab);
		node<T>* 	PARENT(node<T>* n);
		node<T>* 	LEFTMOST_CHILD(node<T>* n);
		node<T>* 	LEFTMOST_CHILD();
		node<T>* 	RIGHT_SIBLING(node<T>* n);
		node<T>* 	ROOT();

		label* 		LABEL(node<T>* n);
		void 		SET_LABEL(node<T>* n, label* l);
		void		SET_ROOT_VALUE(T r);

		void 		MAKENULL();
		void		destroy();

		Tree<T>*	CREATE(label* v, std::initializer_list<Tree<T>*> args);
		List::List<node<T>*> CHILDREN();
	};

	// Construct NULL Tree
	template<typename T>
	Tree<T>::Tree()
	{
		MAKENULL();
	}

	// Construct Tree with given label
	template<typename T>
	Tree<T>::Tree(label* lab)
	{
		MAKENULL();
		root->label = lab;
	}

	template<typename T>
	node<T>* Tree<T>::PARENT(node<T>* n)
	{
		return n->parent;
	}

	template<typename T>
	void Tree<T>::free_node(node<T>* n) // Free node and all its children
	{
		if (n->children->num_elements() > 0)
		{
			List::node<node<T>*>* p = n->children->front();

			for (int i = 0; i < n->children->num_elements(); i++) // For each child
			{
				free_node(p->data); 			// Recursive free_node call
				std::free(p->data->children); 	// Free that node's components
				std::free(p->data->label);
				std::free(p->data);
				p = p->next; 					// Move on to the next
			}
		}
		std::free(n->children);
		std::free(n->label);
		std::free(n);
	}

	template<typename T>
	void Tree<T>::destroy()
	{
		free_node(root);
	}

	template<typename T>
	node<T>* Tree<T>::LEFTMOST_CHILD(node<T>* n)
	{
		List::List<node<T>*>* L;

		L = n->children;

		if (L->empty())
		{
			return NULL;
		} else {
			return L->front()->data;
		}
	}

	template<typename T>
	node<T>* Tree<T>::LEFTMOST_CHILD()
	{
		List::List<node<T>*>* L;

		L = root->children;

		if (L->empty())
		{
			return NULL;
		} else {
			return L->front()->data;
		}
	}

	template<typename T>
	node<T>* Tree<T>::RIGHT_SIBLING(node<T>* child)
	{
		node<T>* parent;
		TreeLOC::node<T>* result;
		List::node<node<T>*>* location;

		List::List<node<T>*>* L;

		/* nodes make use of a pointer to their parent node to find sibling,
		 * this could be simplified if the List::node<T> object was made to
		 * have a NEXT() function as a member, rather than needing to call
		 * the function through a tree.
		 */

		parent = child->parent;

		if (parent == NULL)
		{
			return NULL;
		}

		L = parent->children;

		location = L->locate(child);
		result = L->next(location)->data;

		if (result == NULL || location == parent->children->back())
		{
			return NULL;
		}

		return result;
	}

	template<typename T>
	label* Tree<T>::LABEL(node<T>* n)
	{
		return n->label;
	}

	template<typename T>
	void Tree<T>::SET_LABEL(node<T>* n, label* l)
	{
		n->label = *l;
	}


	/* A generic CREATE() function which takes a label 'v', and an initializer
	 * list, (which is guaranteed to evaluate in the given order), to create
	 * a tree with any number of children. CREATEn() functions simply refer
	 * back to this function.
	 */
	template<typename T>
	Tree<T>* Tree<T>::CREATE(label* v, std::initializer_list<Tree<T>*> args)
	{
		List::List<Tree<T>*>* trees = new List::List<Tree<T>*>;
		Tree<T>* new_tree = new Tree<T>;
		Tree<T>* const* it;

		if (v == NULL)
		{
			v = new label;
		}

		for (it = args.begin(); it != args.end(); it++)
		{
			trees->push_back(*it);
		}

		while (!trees->empty())
		{
			/* If this pointer to a node is the same location in memory as
			 * the next pointer, create a copy of that node so that they can
			 * function autonomously (sibling and child ops)
			 */
			if (trees->front()->data == trees->next(trees->front())->data)
			{
				node<T>* new_tree_node = new node<T>;
				*new_tree_node = *(trees->next(trees->front())->data->root);

				new_tree->root->children->push_back(new_tree_node);
				new_tree->root->children->back()->data->parent = new_tree->root;
			} else {
				new_tree->root->children->push_back(trees->front()->data->root);
				new_tree->root->children->back()->data->parent = new_tree->root;
			}

			trees->pop_front();

		}

		new_tree->root->label = v;

		return new_tree;
	}

	template<typename T>
	Tree<T>* CREATE0(label* v)
	{
		Tree<T>* new_tree = new Tree<T>(v);
		return new_tree;
	}

	template<typename T>
	Tree<T>* CREATE1(label* v, Tree<T>* T1)
	{
		Tree<T>* new_tree = new Tree<T>;
		return new_tree->CREATE(v, {T1});
	}

	template<typename T>
	Tree<T>* CREATE2(label* v, Tree<T>* T1, Tree<T>* T2)
	{
		Tree<T>* new_tree = new Tree<T>;
		return new_tree->CREATE(v, {T1, T2});
	}

	template<typename T>
	Tree<T>* CREATE3(label* v, Tree<T>* T1, Tree<T>* T2, Tree<T>* T3)
	{
		Tree<T>* new_tree = new Tree<T>;
		return new_tree->CREATE(v, {T1, T2, T3});
	}

	template<typename T>
	Tree<T>* CREATE4(label* v, Tree<T>* T1, Tree<T>* T2, Tree<T>* T3,
			Tree<T>* T4)
	{
		Tree<T>* new_tree = new Tree<T>;
		return new_tree->CREATE(v, {T1, T2, T3, T4});
	}

	template<typename T>
	node<T>* Tree<T>::ROOT()
	{
		return root;
	}

	template<typename T>
	void Tree<T>::MAKENULL()
	{
		root = new node<T>;
		root->children = new List::List<node<T>*>;
		root->label = new label;
		root->parent = NULL;
	}

}

