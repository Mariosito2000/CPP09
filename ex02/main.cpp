#include "PmergeMe.hpp"

int main(int argc, char **argv)
{
	if (argc == 1)
	{
		std::cerr << "Error: no input\n";
		return (1);
	}
	try
	{
		PmergeMe(argc, argv);
	}
	catch(const char * e)
	{
		std::cerr << e << '\n';
		return (1);
	}
	return (0);
}