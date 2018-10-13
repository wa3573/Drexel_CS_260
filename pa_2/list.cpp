/*
 * 	Generic list implementation
 *
 *  Created on: Jul 11, 2018
 *      Author: William Anderson
 */

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>


namespace List
{

	template<typename T>
	struct node {
		T 			data;
//		int 		label;
		node<T>* 	next;
		node<T>* 	prev;
		node<T>*	get_next();
		node<T>*	get_previous();
	};

	template<typename T>
	node<T>* node<T>::get_next()
	{
		return next;
	}

	template<typename T>
	node<T>* node<T>::get_previous()
	{
		return prev;
	}

	template<typename T>
	class List
	{
	private:
		node<T>*	head;
		node<T>*	tail;
		size_t 		element_size;
		int 		compare_elements(T* lhs, T* rhs);
		void 		free_node(node<T>* n);
		void 		init();
	 public:
					List();
					~List() {destroy();}
		int 		logical_length;
		node<T>* 	front();
		node<T>* 	back();
		node<T>* 	next(node<T>* p);
		node<T>* 	previous(node<T>* p);
		int			num_elements();
		bool 		contains(T data);
		void 		push_front(T data);
		void	 	push_back(T data);
		void		insert(T data, node<T>* p);
		void 		pop_front();
		void 		pop_back();
		void 		remove_node(node<T>* p);
		void 		remove_element(T data);
		bool 		empty();
		void		destroy();
		node<T>* 	locate(T data);

	};

	template<typename T>
	List<T>::List()
	{
		init();
	}

	template<typename T>
	void List<T>::free_node(node<T>* n)
	{
		delete n;
	}

	template<typename T>
	int List<T>::num_elements()
	{
		return logical_length;
	}

	template<typename T>
	int List<T>::compare_elements(T* lhs, T* rhs)
	{
		T* llhs = (T*)lhs;
		T* lrhs = (T*)rhs;

		if (*llhs < *lrhs)
		{
			return -1;
		} else if (*llhs > *lrhs) {
			return 1;
		}

		return 0;
	}

	template<typename T>
	void List<T>::init()
	{
		head = new node<T>;
		tail = new node<T>;

		if (head == NULL || tail == NULL)
		{
			perror("new");
			exit(EXIT_FAILURE);
		}

		logical_length = 0;
		element_size = sizeof(T);

		head->next = tail;
		head->prev = NULL;
		tail->next = NULL;
		tail->prev = head;
	}

	template<typename T>
	node<T>* List<T>::front()
	{
		return head->next;
	}

	template<typename T>
	node<T>* List<T>::back()
	{
		return tail->prev;
	}

	template<typename T>
	node<T>* List<T>::next(node<T>* p)
	{
		return p->next;
	}

	template<typename T>
	node<T>* List<T>::previous(node<T>* p)
	{
		return p->prev;
	}

	template<typename T>
	bool List<T>::empty()
	{
		if (head->next == tail && tail->prev == head)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	void List<T>::push_front(T data)
	{
		node<T>* n = new node<T>;
		n->data = data;
		n->prev = head;

		node<T>* p = head;
		node<T>* temp = head->next;

		p->next = n;
		n->prev = p;
		n->next = temp;
		temp->prev = n;

		logical_length++;
	}

	template<typename T>
	void List<T>::push_back(T data)
	{
		node<T>* n = new node<T>;
		n->data = data;
		n->next = tail;

		node<T>* p = tail->prev;

		p->next = n;
		n->next = tail;
		n->prev = p;
		tail->prev = n;

		logical_length++;
	}


	template<typename T>
	void List<T>::insert(T data, node<T>* p)
	{
		node<T>* n = new node<T>;
		node<T>* temp = p->next;

		n->data = data;
		n->next = tail;

		p->next = n;
		n->next = temp;
		n->prev = p;

		if (temp != NULL)
		{
			temp->prev = n;
		}

		logical_length++;
	}

	template<typename T>
	void List<T>::pop_front()
	{
		if (empty())
		{
			fprintf(stderr, "Error: list is empty \n");
		} else {
			node<T>* temp = head->next;
			node<T>* p = temp->next;

			head->next = p;
			p->prev = head;
			delete temp;

			logical_length--;
		}
	}

	template<typename T>
	void List<T>::remove_node(node<T>* p)
	{
		if (p == head)
		{
			fprintf(stderr, "Error: cannot delete head \n");
		} else if (p == tail) {
			fprintf(stderr, "Error: cannot delete head \n");
		} else {
			node<T>* temp = p;
			node<T>* q = p->prev;
			node<T>* r = p->next;

			q->next = r;
			r->prev = q;
			std::free(temp);

			logical_length--;
		}
	}

	template<typename T>
	void List<T>::remove_element(T data)
	{
		node<T>* p = front();
		pid_t* ldata = (pid_t*)data;

		while (p->next != NULL)
		{
			if (*((pid_t*)(p->data)) == *ldata)
			{
				remove_node(p);
				break;
			}

			p = p->next;
		}
	}

	template<typename T>
	void List<T>::pop_back()
	{
		if (tail->prev == head)
		{

		} else {
			node<T>* temp = tail->prev;
			node<T>* p = temp->prev;

			tail->prev = p;
			p->next = tail;

			std::free(temp);

			logical_length--;
		}
	}

	template<typename T>
	bool List<T>::contains(T data)
	{
		bool result = false;

		node<T>* p = head->next;

		while (p->next != NULL)
		{
			if (compare_elements(p->data, data) == 0)
			{
				result = true;
				break;
			}
			p = p->next;
		}

		return result;
	}

	template<typename T>
	node<T>* List<T>::locate(T data)
	{
		node<T>* result = NULL;

		node<T>* p = head->next;

		while (p->next != NULL)
		{
			if (compare_elements(&p->data, &data) == 0)
			{
				result = p;
				break;
			}
			p = p->next;
		}

		return result;
	}

	template<typename T>
	void List<T>::destroy()
	{
		node<T>* temp = head->next;

		while (temp != tail) 	// Free all list nodes
		{
			head->next = temp->next;
			temp->next->prev = head;
			free_node(temp);

			temp = head->next;
		}
	}

	template<typename T>
	void display_list(List<T>* t)
	{
		node<T>* p = t->front();
		while (p != t->next(t->back()))
		{
			std::cout << "[" << p->data << "]->";
			p = t->next(p);
		}
		std::cout << "END \n";
	}

}
