/*
 * traversalconvert.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: Juniper
 */


#include "loctree.cpp"

int count = 0; 	// for traverse debug
static volatile bool VERBOSE = false;

template<typename T>
void t_traverse_pre_LOC(TreeLOC::Tree<T>* t, TreeLOC::node<T>* n, List::List<std::string>* out)
{
	TreeLOC::node<T>* c;

//	if (count > 25)
//	{
//		return;
//	}

	/* Code here for preorder ops */
	out->push_back(t->LABEL(n)->value);
	if (VERBOSE)
	{
		std::cout << t->LABEL(n)->value << ", ";
	}
	c = t->LEFTMOST_CHILD(n);
	count++;

	while (c != NULL)
	{
		t_traverse_pre_LOC(t, c, out);
		c = t->RIGHT_SIBLING(c);
	}


}

template<typename T>
void t_traverse_post_LOC(TreeLOC::Tree<T>* t, TreeLOC::node<T>* n, List::List<std::string>* out)
{
	TreeLOC::node<T>* c;

//	if (count > 25)
//	{
//		return;
//	}

	c = t->LEFTMOST_CHILD(n);
	count++;

	while (c != NULL)
	{
		t_traverse_post_LOC(t, c, out);
		c = t->RIGHT_SIBLING(c);
	}

	/* Code here for postorder ops */
	out->push_back(t->LABEL(n)->value);
	if (VERBOSE)
	{
		std::cout << t->LABEL(n)->value << ", ";
	}


}

template<typename T>
void t_traverse_in_LOC(TreeLOC::Tree<T>* t, TreeLOC::node<T>* n, List::List<std::string>* out)
{
	TreeLOC::node<T>* c;

//	if (count > 25)
//	{
//		return;
//	}
	if (n->LEFTMOST_CHILD() == NULL)
	{
		out->push_back(t->LABEL(n)->value);
		if (VERBOSE)
		{
			std::cout << t->LABEL(n)->value << ", ";
		}
	} else {
		c = t->LEFTMOST_CHILD(n);
		count++;

		t_traverse_in_LOC(t, c, out);

		/* Code here for inorder ops */
		out->push_back(t->LABEL(n)->value);

		if (VERBOSE)
		{

			std::cout << t->LABEL(n)->value << ", ";
		}

		c = t->RIGHT_SIBLING(c);
		while (c != NULL)
		{
			t_traverse_in_LOC(t, c, out);
			c = t->RIGHT_SIBLING(c);
		}
	}


}

template<typename T>
TreeLOC::Tree<T>* create_t_from_post(List::List<std::string>* li_post)
{
	List::node<std::string>* p_a;
	List::node<std::string>* p_b;
	TreeLOC::label* label_left;
	TreeLOC::label* label_right;
	TreeLOC::label* label_parent;
	TreeLOC::Tree<T>* tree_left;
	TreeLOC::Tree<T>* tree_right;
	TreeLOC::Tree<T>* tree_temp;

	bool first = true;

	/* initialize pointers to the front and back of the postorder list */
	p_a = li_post->front();
	p_b = li_post->back();

	/* traverse the list and create a tree which has the given postorder  */
	while (p_a != p_b)
	{
		if (first)
		{
			label_left = new TreeLOC::label (p_a->data);
			label_right = new TreeLOC::label (p_a->get_next()->data);

			tree_left = new TreeLOC::Tree<int>(label_left);
			tree_right = new TreeLOC::Tree<int>(label_right);

			first = false;
		} else {
			label_right = new TreeLOC::label(p_a->get_next()->data);
			tree_left = tree_temp;
			tree_right = new TreeLOC::Tree<int>(label_right);
		}

		label_parent = new TreeLOC::label(p_a->get_next()->get_next()->data);
		if (VERBOSE)
		{
			std::cout << "Creating tree with root label: " << label_parent->value
					<< " left child label: " << tree_left->ROOT()->label->value << " right child label: "
					<< tree_right->ROOT()->label->value << std::endl;
		}
		tree_temp = TreeLOC::CREATE2(label_parent, tree_left, tree_right);
		p_a = p_a->get_next()->get_next();
	}

	return tree_temp;
}


template<typename T>
TreeLOC::Tree<T>* create_t_from_pre(List::List<std::string>* li_pre)
{
	List::node<std::string>* p_a;
	List::node<std::string>* p_b;
	TreeLOC::label* label_left;
	TreeLOC::label* label_right;
	TreeLOC::label* label_parent;
	TreeLOC::Tree<T>* tree_left;
	TreeLOC::Tree<T>* tree_right;
	TreeLOC::Tree<T>* tree_temp;

	bool first = true;

	/* initialize pointers to the front and back of the postorder list */
	p_a = li_pre->front()->get_next();
	p_b = li_pre->back();


	/* traverse until pointers cross each other, at the middle */
	while (p_a->get_previous() != p_b)
	{
		p_a = p_a->get_next();
		p_b = p_b->get_previous();
	}

	/* traverse the rest of the list and create a tree which has the given postorder  */
	while (p_a->get_previous() != li_pre->back())
	{
		if (first)
		{
			label_left = new TreeLOC::label (p_b->data);
			label_right = new TreeLOC::label (p_a->data);

			tree_left = new TreeLOC::Tree<int>(label_left);
			tree_right = new TreeLOC::Tree<int>(label_right);

			first = false;
		} else {
			label_right = new TreeLOC::label(p_a->data);
			tree_left = tree_temp;
			tree_right = new TreeLOC::Tree<int>(label_right);
		}

		label_parent = new TreeLOC::label(p_b->get_previous()->data);
		if (VERBOSE)
		{
			std::cout << "Creating tree with root label: " << label_parent->value
					<< " left child label: " << tree_left->ROOT()->label->value << " right child label: "
					<< tree_right->ROOT()->label->value << std::endl;
		}
		tree_temp = TreeLOC::CREATE2(label_parent, tree_left, tree_right);

		p_a = p_a->get_next();
		p_b = p_b->get_previous();
	}

	return tree_temp;
}

List::List<std::string>* pre_to_post(List::List<std::string>* pre)
{
	TreeLOC::Tree<int>* constructed;
	List::List<std::string>* new_list = new List::List<std::string>;

	// construct tree from preorder
	constructed = create_t_from_pre<int>(pre);

	// run standard traversal
	t_traverse_post_LOC(constructed, constructed->ROOT(), new_list);

	return new_list;

}

List::List<std::string>* post_to_pre(List::List<std::string>* post)
{
	TreeLOC::Tree<int>* constructed;
	List::List<std::string>* new_list = new List::List<std::string>;

	// construct tree from postorder
	constructed = create_t_from_post<int>(post);

	// run standard traversal
	t_traverse_pre_LOC(constructed, constructed->ROOT(), new_list);

	return new_list;
}

List::List<std::string>* pre_to_in(List::List<std::string>* pre)
{
	TreeLOC::Tree<int>* constructed;
	List::List<std::string>* new_list = new List::List<std::string>;

	// construct tree from preorder
	constructed = create_t_from_pre<int>(pre);

	// run standard traversal
	t_traverse_in_LOC(constructed, constructed->ROOT(), new_list);

	return new_list;
}
int main(int argc, char** argv)
{
	List::List<std::string>* pre = new List::List<std::string>();
	List::List<std::string>* post = new List::List<std::string>();
	List::List<std::string>* in = new List::List<std::string>();

	// Initialize list which holds preorder sequence
	pre->push_back("A");
	pre->push_back("B");
	pre->push_back("C");
	pre->push_back("D");
	pre->push_back("E");
	pre->push_back("F");
	pre->push_back("G");
	pre->push_back("H");
	pre->push_back("I");

	std::cout << "\nGiven, Preorder: \n";
	List::display_list(pre); // @suppress("Invalid arguments")

	post = pre_to_post(pre);
	std::cout << "Converted, Postorder: \n";
	List::display_list(post); // @suppress("Invalid arguments")

	in = pre_to_in(pre);
	std::cout << "Converted, Inorder: \n";
	List::display_list(in); // @suppress("Invalid arguments")

	delete post;
	post = new List::List<std::string>();

	// Initialize list which holds postorder sequence
	post->push_back("E");
	post->push_back("F");
	post->push_back("D");
	post->push_back("G");
	post->push_back("C");
	post->push_back("H");
	post->push_back("B");
	post->push_back("I");
	post->push_back("A");

	std::cout << "\nGiven, Postorder: \n";
	List::display_list(post); // @suppress("Invalid arguments")

	pre = post_to_pre(post);
	std::cout << "Converted, Preorder: \n";
	List::display_list(pre); // @suppress("Invalid arguments")
}
