/*
 * tree_loc_cursor.cpp
 *
 *  Created on: Aug 8, 2018
 *      Author: Juniper
 */

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <initializer_list>
#include <cstdint>
#include <cstring>

#define T_LCRS_CUR_SPACE_SIZE 100
#define T_LCRS_CUR_LABEL_SIZE 32

namespace TreeLCRS_cur
{
	typedef unsigned int node_ptr;
	typedef node_ptr position;

	template<typename T>
	class Tree;

	template<typename T>
	struct node;

	/* This functions as the shared cursor space that enables the creation
	 * of trees from subtrees, it must be declared under the same namespace
	 * (TreeLCRS_cur) when used. See timing.cpp for an example
	 */
	template<typename T>
	node<T> CURSOR_SPACE[T_LCRS_CUR_SPACE_SIZE];

	extern bool CURSOR_SPACE_INITIALIZED;
	extern node_ptr	avail;

	struct label {
		char value[T_LCRS_CUR_LABEL_SIZE];
	};

	template<typename T>
	struct node
	{
		TreeLCRS_cur::label		label;
		T			data;
		node_ptr	parent;
		node_ptr	left_child;
		node_ptr	right_sib;
		node<T> 	LEFTMOST_CHILD();
		node<T> 	RIGHT_SIBLING();
	};

	template<typename T>
	node<T> node<T>::LEFTMOST_CHILD()
	{
		return CURSOR_SPACE<T>[left_child];
	}


	template<typename T>
	node<T> node<T>::RIGHT_SIBLING()
	{
		return CURSOR_SPACE<T>[right_sib];
	}

	template<typename T>
	class Tree
	{

		position 	cursor_alloc();
		void 		cursor_free(position p);

		node_ptr	root;
		void		free_node(node<T> n);
	public:
					Tree();
					Tree(label lab);
		node<T>		PARENT(node<T> n);
		node<T> 	LEFTMOST_CHILD(node<T> n);
		node<T> 	LEFTMOST_CHILD();
		node<T> 	RIGHT_SIBLING(node<T> n);

		label 		LABEL(node<T> n);
		void		SET_ROOT_DATA(T r);

		node<T> 	ROOT();
		void 		MAKENULL();
		void		destroy();
		Tree<T>		CREATE(label v, std::initializer_list<Tree<T>> args);

	};

	template<typename T>
	position Tree<T>::cursor_alloc()
	{
		position p_old;
		p_old = avail;
		avail = CURSOR_SPACE<T>[p_old].right_sib;

		return p_old;
	}

	template<typename T>
	void Tree<T>::cursor_free(position p)
	{
		position avail_old = avail;

		avail = p;
		CURSOR_SPACE<T>[p].right_sib = avail_old;
	}

	template<typename T>
	Tree<T>::Tree()
	{
		if (!CURSOR_SPACE_INITIALIZED)
		{
			avail = 1;
			/* Link available cells by right sibling */
			for (int i = avail; i < T_LCRS_CUR_SPACE_SIZE; i++)
			{
				CURSOR_SPACE<T>[i].right_sib = i + 1;
			}

			CURSOR_SPACE_INITIALIZED = true;
		}

		MAKENULL();
	}

	template<typename T>
	Tree<T>::Tree(label lab)
	{
		if (!CURSOR_SPACE_INITIALIZED)
		{
			avail = 1;
			/* Link available cells by right sibling */
			for (int i = avail; i < T_LCRS_CUR_SPACE_SIZE; i++)
			{
				CURSOR_SPACE<T>[i].right_sib = i + 1;
			}

			CURSOR_SPACE_INITIALIZED = true;
		}

		MAKENULL();
		std::memcpy(CURSOR_SPACE<T>[root].label.value, lab.value, T_LCRS_CUR_LABEL_SIZE);

	}

	template<typename T>
	void Tree<T>::MAKENULL()
	{
		position pos_new_root = cursor_alloc();

		root = pos_new_root;
		CURSOR_SPACE<T>[root].left_child = 0;
		CURSOR_SPACE<T>[root].right_sib = 0;
		CURSOR_SPACE<T>[root].parent = 0;
	}

	template<typename T>
	label Tree<T>::LABEL(node<T> n)
	{
		return n.label;
	}

	template<typename T>
	node<T> Tree<T>::LEFTMOST_CHILD(node<T> n)
	{
		return n.LEFTMOST_CHILD();
	}

	template<typename T>
	node<T> Tree<T>::LEFTMOST_CHILD()
	{
		return CURSOR_SPACE<T>[root].LEFTMOST_CHILD();
	}


	template<typename T>
	node<T> Tree<T>::RIGHT_SIBLING(node<T> n)
	{
		return n.RIGHT_SIBLING();
	}

	template<typename T>
	node<T> Tree<T>::PARENT(node<T> n)
	{
		return CURSOR_SPACE<T>[n.parent];
	}

	template<typename T>
	node<T> Tree<T>::ROOT()
	{
		return CURSOR_SPACE<T>[root];
	}

	template<typename T>
	void Tree<T>::SET_ROOT_DATA(T data)
	{
		CURSOR_SPACE<T>[root].data = data;
	}


	template<typename T>
	Tree<T> CREATE0(label v)
	{
		Tree<T> new_tree = Tree<T>(v);

		return new_tree;
	}

	template<typename T>
	Tree<T> CREATE1(label v, Tree<T> T1)
	{
		Tree<T> new_tree = Tree<T>(v);
		return new_tree.CREATE(v, {T1});
	}

	template<typename T>
	Tree<T> CREATE2(label v, Tree<T> T1, Tree<T> T2)
	{
		Tree<T> new_tree = Tree<T>(v);
		return new_tree.CREATE(v, {T1, T2});
	}

	template<typename T>
	Tree<T> CREATE3(label v, Tree<T> T1, Tree<T> T2, Tree<T> T3)
	{
		Tree<T> new_tree = Tree<T>(v);
		return new_tree.CREATE(v, {T1, T2, T3});
	}

	template<typename T>
	Tree<T> CREATE4(label v, Tree<T> T1, Tree<T> T2, Tree<T> T3,
			Tree<T> T4)
	{
		Tree<T> new_tree = Tree<T>(v);
		return new_tree.CREATE(v, {T1, T2, T3, T4});
	}

	/* A generic CREATE() function which takes a label 'v', and an initializer
	 * list, (which is guaranteed to evaluate in the given order), to create
	 * a tree with any number of children. CREATEn() functions simply refer
	 * back to this function.
	 */
	template<typename T>
	Tree<T> Tree<T>::CREATE(label v, std::initializer_list<Tree<T>> args)
	{
		Tree<T> new_tree = Tree<T>();
		Tree<T> const* it = args.begin();

		position pos_new_root = cursor_alloc();
		position curr_pos = pos_new_root;

		new_tree.root = pos_new_root;
		CURSOR_SPACE<T>[pos_new_root].label = v;

		/* if the initializer_list is empty */
		if (args.begin() == args.end())
		{
			return new_tree;
		} else {
		/* Make the first argument the leftmost child of the new root */
			position new_pos = cursor_alloc();
			curr_pos = new_pos;
			position node_arg_root = (*args.begin()).root;

			CURSOR_SPACE<T>[new_tree.root].left_child = new_pos;
			CURSOR_SPACE<T>[new_pos] = CURSOR_SPACE<T>[node_arg_root];
			CURSOR_SPACE<T>[new_pos].parent = new_tree.root;

			/* For the rest of the arguments, add them as right siblings to the last */
			for (it = args.begin() + 1; it != args.end(); it++)
			{
				Tree<T> arg_tree = (*it);
				position pos_arg_tree = arg_tree.root;
				new_pos = cursor_alloc();
				CURSOR_SPACE<T>[curr_pos].right_sib = new_pos;
				CURSOR_SPACE<T>[new_pos] = CURSOR_SPACE<T>[arg_tree.root];
				CURSOR_SPACE<T>[new_pos].label = CURSOR_SPACE<T>[pos_arg_tree].label;
				curr_pos = new_pos;

			}

			CURSOR_SPACE<T>[curr_pos].right_sib = 0;
		}

		return new_tree;
	}



}
