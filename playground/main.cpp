/*
 * main.cpp
 *
 *  Created on: Aug 3, 2018
 *      Author: Juniper
 */
#include <iostream>
#include <string>
#include <tuple>
#include "list.cpp"


struct il_to_list {
	List::List<int> list;
	il_to_list(std::initializer_list<int> args)
	{
		std::initializer_list<int>::iterator it;
		for (it = args.begin(); it != args.end(); it++)
		{
			list.push_back(*it);
		}

	}
};

template<typename T>
List::List<T> create(std::initializer_list<T> il) {
	List::List<T> L;

	const int* it;

	for (it = il.begin(); it != il.end(); it++)
	{
		L.push_back(*it);
	}

	return L;
}

/* clrstdin() clear any leftover chars tha may be in stdin stream */
void clrstdin( void )
{
   int ch = 0;

   while( ( ch = getchar() ) != '\n' && ch != EOF )
         ;
}

int main(int argc, char** argv)
{
	char input[32];
	int num;
	double res;

//	std::fgets(input, sizeof(input), stdin);
//	if (sscanf(input, " %d", &num) != 1)
//	{
//		std::cout << "Error parsing input \n";
//	}

	for (num = 0; num < 20; num++)
	{
		res = ((double)num / 2) - 1;

		std::cout << "input = " << num << "\tdouble = " << res << "\t(int) = " << (int)res << std::endl;
	}

}

