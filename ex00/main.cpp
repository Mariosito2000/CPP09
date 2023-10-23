#include "BitcoinExchange.hpp"
#include "iostream"

int	main (int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Error: Incorrect number of arguments\n";
		std::exit(1);
	}
	try
	{
		std::map <std::string, std::string> map;
		parse_csv(map);
		//parse_file();
		//execute();
		(void) argv;
	}
	catch(const char *e) //cambiar por std::exception
	{
		std::cerr << e << '\n';
		return (1);
	}
	return (0);
}