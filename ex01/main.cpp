#include "RPN.hpp"

int	main(int argc, char ** argv)
{
	if (argc < 2)
	{
		std::cerr << "Error: wrong number of arguments\n";
		return (1);
	}
	try
	{
		RPN(argv[1]);
	}
	catch(const char *e)
	{
		std::cerr << e << '\n';
		return (1);
	}
	return (0);
}