#include "BitcoinExchange.hpp"

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Incorrect number of arguments\n";
		return (1);
	}
	try
	{
		std::map <std::string, std::string> map;
		parse_csv(map);
		execute_exchange(argv[1], map);
	}
	catch(const std::string e)
	{
		std::cerr << e << '\n';
		std::exit(1);
	}
	catch(const char *e)
	{
		std::cerr << e << '\n';
		std::exit(1);
	}
	
	return (0);
}