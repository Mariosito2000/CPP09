#include "BitcoinExchange.hpp"

static void	check_date_exceptions(tm &date)
{
	if (date.tm_mday == 0)
		throw ("day0");
	if ((date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10) && date.tm_mday > 30)
		throw ("mal n dias");
	if (date.tm_mon == 1 && (date.tm_year + 1900) % 4 == 0 && ((date.tm_year + 1900) % 100 != 0 || (date.tm_year + 1900) % 400 == 0) && date.tm_mday > 29)
		throw ("mal bisiesto dias");
	if (date.tm_mon == 1 && !((date.tm_year + 1900) % 4 == 0 && ((date.tm_year + 1900) % 100 != 0 || (date.tm_year + 1900) % 400 == 0)) && date.tm_mday > 28)
		throw ("mal no bisiesto dias");
}

static void	check_date(std::string&	key)
{
	if (key.empty() || key.length() > 10)
		throw("Failure terrible");
	if (key[4] != '-' || key[7] != '-')
		throw("CSVwrogformat");
	for (size_t	i = 0; i < 4; i++)
		if (!std::isdigit(key[i]))
			throw("Failure terrible Y");
	for (size_t	i = 5; i < 7; i++)
		if (!std::isdigit(key[i]))
			throw("Failure terrible M");
	for (size_t	i = 8; i < 10; i++)
		if (!std::isdigit(key[i]))
			throw("Failure terrible D");
	std::cout << "key = " << key << "\n";
	tm date;
	if (!strptime(key.c_str(), "%Y-%m-%d", &date))
		throw("strptime fail");
	check_date_exceptions(date);
}

static void	check_value_csv(std::string& value)
{
	bool point = false;
	if (value.empty() || value[value.length() - 1] == '.' || value[0] == '.')
		throw("invalid value wrongpos point");
	for (size_t i = 0; i < value.length(); i++)
	{
		if (!std::isdigit(value[i]) && value[i] != '.')
			throw("invalid value");
		if (value[i] == '.')
		{
			if (point == true)
				throw("invalid value point");
			point = true;
		}
	}
}

//static void	add2map(std::map <std::string, std::string> map, std::string key, std::string value);

void	parse_csv(std::map <std::string, std::string> map)
{
	std::fstream 		database;
	std::stringstream	line;
	std::string			string, key, value;

	database.open("data.csv");
	if (!database.is_open())
		throw (/* DatabaseFailedToOpenException() */"Fallo");
	getline(database, string);
	string.clear();
	while (std::getline(database, string))
	{
		(void)map;
		std::cout << "string = " << string << "\n";
		line << string;
		std::getline(line, key, ',');
		check_date(key);
		std::getline(line, value, '\n');
		check_value_csv(value);
		map.insert(std::make_pair(key, value));
		line.clear();
	}
	for (std::map<std::string, std::string>::iterator it = map.begin(); it != map.end(); it++)
	{
		std::cout << it->second << "\n";
	}
}