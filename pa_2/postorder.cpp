/*
 * postorder.cpp
 *
 *  Created on: Aug 13, 2018
 *      Author: Juniper
 */

#include "loctree.cpp"
#include <string>
#include <regex>


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

bool is_op(std::string in)
{
	std::regex reg = std::regex(R"(^[\+*])");
	if (std::regex_match (in, reg ))
	{
		return true;
	}

	return false;
}

int do_math(std::string left, std::string right, std::string op)
{
	std::string::size_type sz;   // alias of size_t

	int term_1 = std::stoi(left, &sz);
	int term_2 = std::stoi(right, &sz);
	int res;

	if (op.compare("+") == 0)
	{
		res = term_1 + term_2;
	} else if (op.compare("-") == 0)
	{
		res = term_1 - term_2;
	} else if (op.compare("*") == 0)
	{
		res = term_1 * term_2;
	} else if (op.compare("/") == 0)
	{
		res = term_1 / term_2;
	} else if (op.compare("%") == 0)
	{
		res = term_1 % term_2;
	} else if (op.compare("^") == 0)
	{
		res = term_1 ^ term_2;
	}

	return res;
}

void t_simplify(TreeLOC::Tree<std::string>* t, TreeLOC::node<std::string>* n)
{
	if (is_op(n->LEFTMOST_CHILD()->value))
	{
		t_simplify(t, n->LEFTMOST_CHILD());
	}

	if (is_op(n->LEFTMOST_CHILD()->RIGHT_SIBLING()->value))
	{
		t_simplify(t, n->LEFTMOST_CHILD()->RIGHT_SIBLING());
	}

	if (is_number(n->LEFTMOST_CHILD()->value) && is_number(n->LEFTMOST_CHILD()->RIGHT_SIBLING()->value))
	{
		std::string left = n->LEFTMOST_CHILD()->value;
		std::string right = n->LEFTMOST_CHILD()->RIGHT_SIBLING()->value;
		std::string op = n->value;

		std::cout << "Doing math: " << left << " " << op << " " << right << std::endl;
		int res = do_math(left, right, op);

		std::cout << "Result: " << res << std::endl;
		n->set_value(std::to_string(res));
	}

}

int calculate_tree(TreeLOC::Tree<std::string>* t)
{
	int res;
	std::string::size_type sz;   // alias of size_t

	while (is_op(t->ROOT()->value))
	{
		t_simplify(t, t->ROOT());
	}

	res = std::stoi(t->ROOT()->value, &sz);

	return res;
}

void display_list_root_values(List::List<TreeLOC::Tree<std::string>*>* t)
{
	List::node<TreeLOC::Tree<std::string>*>* p = t->front();
	while (p != t->next(t->back()))
	{
		std::cout << "[" << p->data->ROOT()->value << "]->";
		p = t->next(p);
	}
	std::cout << "END \n";
}

TreeLOC::Tree<std::string>* t_create_from_postfix(List::List<std::string>* post)
{
	TreeLOC::Tree<std::string>* t_temp = new TreeLOC::Tree<std::string>();
	TreeLOC::Tree<std::string>* t_left = new TreeLOC::Tree<std::string>();
	TreeLOC::Tree<std::string>* t_right = new TreeLOC::Tree<std::string>();
	List::List<TreeLOC::Tree<std::string>*>* li_gen = new List::List<TreeLOC::Tree<std::string>*>;

	List::node<std::string>* c1;
	List::node<TreeLOC::Tree<std::string>*>* c2;

	int ops_visited = 0;
	int i;

	c1 = post->front();

	// Initialize list of trees
	while(c1->get_next() != NULL)
	{
		t_temp = new TreeLOC::Tree<std::string>();
		t_temp->ROOT()->set_value(c1->data);

		li_gen->push_back(t_temp);

		c1 = c1->get_next();
	}



	while (li_gen->logical_length > 1)
	{
		c2 = li_gen->front();
//		std::cout << "c2 @ " << c2->data << std::endl;
//		std::cout << "c2 data = " << c2->data->ROOT()->value << ", is_op() == " << is_op(c2->data->ROOT()->value) << std::endl;
//
//		List::display_list(li_gen); // @suppress("Invalid arguments")
//		display_list_root_values(li_gen);

		i = 0;
		// traverse until operator

		while (1)
		{
			if (c2 == li_gen->back())
				break;
			if (is_op(c2->data->ROOT()->value))
			{
				i++;
				if (i > ops_visited)
					break;
			}

			c2 = c2->get_next();
		}

		// op found, pop trees to left, create2()

		// get right child
		t_right = c2->get_previous()->data;
		// pop
		li_gen->remove_node(c2->get_previous());
		// get left child
		t_left = c2->get_previous()->data;
		// pop
		li_gen->remove_node(c2->get_previous());

//		std::cout << "Creating tree with root value: " << c2->data->ROOT()->value
//				<< " left child value: " << t_left->ROOT()->value << " right child label: "
//				<< t_right->ROOT()->value << std::endl;

		TreeLOC::label* label = new TreeLOC::label ("");
		t_temp = TreeLOC::CREATE2(label, t_left, t_right); // @suppress("Invalid arguments")
		t_temp->ROOT()->set_value(c2->data->ROOT()->value);

		li_gen->insert(t_temp, c2);
		// pop op tree
		li_gen->remove_node(c2);

		if(is_op(t_left->ROOT()->value))
			ops_visited--;
		if(is_op(t_right->ROOT()->value))
			ops_visited--;


		ops_visited++;
//
//		// push merged tree
//		li_gen->push_back(t_temp);

	}

	return li_gen->front()->data;

}

int main(int argc, char** argv)
{
	TreeLOC::Tree<std::string>* t_res;

	List::List<std::string>* in = new List::List<std::string>;

	int i_res;

	// Postfix = [ 1 2 + 3 4 5 + * * ]
	in->push_back("1");
	in->push_back("2");
	in->push_back("+");
	in->push_back("3");
	in->push_back("4");
	in->push_back("5");
	in->push_back("+");
	in->push_back("*");
	in->push_back("*");

	std::cout << "Given, Postfix expression: \n";
	List::display_list(in); // @suppress("Invalid arguments")

	t_res = t_create_from_postfix(in);
	i_res = calculate_tree(t_res);

	std::cout << "Calculated result = " << i_res << std::endl;

}
