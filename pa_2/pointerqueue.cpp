/*
 * queue.c
 *
 *  Created on: Jul 31, 2018
 *      Author: Juniper
 */

//#include <stdio.h>
#include <iostream>
//#include <stdlib.h>

namespace Queue
{

	template<typename T>
	struct node {
		T 		value;
		node* 	next;
		node* 	previous;
	};

	template<typename T>
	class Queue
	{

		node<T>* 	head;
		node<T>* 	tail;

	  public:
					Queue();
					~Queue() { destroy(); }
		int 		logical_length;
		node<T>* 	FRONT();
		node<T>* 	BACK();
		bool 		ENQUEUE(T);
		bool 		DEQUEUE();
		bool 		EMPTY();
		void	 	MAKENULL();
		void		destroy();
	};

	template<typename T>
	Queue<T>::Queue()
	{
		MAKENULL();
	}

	template<typename T>
	node<T>* Queue<T>::FRONT()
	{
		return head->previous;
	}

	template<typename T>
	node<T>* Queue<T>::BACK()
	{
		return tail->next;
	}

	template<typename T>
	bool Queue<T>::ENQUEUE(T x)
	{
		node<T>* n = new node<T>;

		n->value = x;
		n->next = tail->next;
		n->previous = tail;
		n->next->previous = n;
		tail->next = n;

		logical_length++;

		return true;
	}

	template<typename T>
	bool Queue<T>::DEQUEUE()
	{
		node<T>* temp = head->previous;

		if (temp != tail)
		{
			head->previous = head->previous->previous;
			head->previous->next = head;

			delete temp;
			logical_length--;

			return true;
		}

		return false;
	}

	template<typename T>
	bool Queue<T>::EMPTY()
	{
		node<T>* p = head->previous;

		if (p == tail)
		{
			return true;
		}

		return false;
	}

	template<typename T>
	void Queue<T>::MAKENULL()
	{
		head = new node<T>;
		tail = new node<T>;

		if (head == NULL || tail == NULL)
		{
			std::cerr << "Error: cannot allocate memory";
		}

		head->next = NULL;
		head->previous = tail;
		tail->next = head;
		tail->previous = NULL;

		logical_length = 0;
	}

	template<typename T>
	void Queue<T>::destroy()
	{
		node<T>* temp;
		node<T>* p = head->previous;

		if (!EMPTY())
		{
			while (p != tail)
			{
				temp = p;
				p = p->previous;

				delete temp;
			}
		}

		delete head;
		delete tail;
	}

}

