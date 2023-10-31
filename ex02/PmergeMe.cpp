#include "PmergeMe.hpp"

static int	arg_to_int(char *arg)
{
	if (!*arg)
		throw ("Error: bad input");
	for(size_t i = 0; i < std::strlen(arg); i++)
		if (!(std::isdigit(arg[i])))
			throw ("Error: bad input");
	return (atoi(arg));
}

static std::chrono::nanoseconds	order_lst(std::list<int> lst)
{
	
}

static void	print_result(std::list<int>	lst, std::chrono::nanoseconds lst_time, std::chrono::nanoseconds vector_time)
{
	std::cout << "After: ";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << " " << *it;
	std::cout << "\nTime to process a range of " << lst.size() << " elements with std::list<int> : " << lst_time.count();
	std::cout << "\nTime to process a range of " << lst.size() << " elements with std::vector<int> : " << vector_time.count() << "\n";
}

void	PmergeMe(int argc, char **argv)
{
	std::list<int>				lst;
	std::chrono::nanoseconds	lst_time;

	std::vector<int>			vector;
	std::chrono::nanoseconds	vector_time;

	int							value;

	for (int i = 1; i < argc; i++)
	{
		value = arg_to_int(argv[i]);
		lst.push_back(value);
		vector.push_back(value);
	}
	std::cout << "Before: ";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << " " << *it;
	std::cout << "\n";
	//lst_time = order_list(lst);
	//vector_time = order_vector(vector);
	//print_result(lst, lst_time, vector_time);
}