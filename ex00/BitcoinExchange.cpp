#include "BitcoinExchange.hpp"

static void	check_date_exceptions(tm &date, std::string& key)
{
	if (date.tm_mday == 0)
		throw ("Error: not a valid date => \"" + key + "\"");
	if ((date.tm_mon == 3 || date.tm_mon == 5 || date.tm_mon == 8 || date.tm_mon == 10) && date.tm_mday > 30)
		throw ("Error: not a valid date => \"" + key + "\"");
	if (date.tm_mon == 1 && (date.tm_year + 1900) % 4 == 0 && ((date.tm_year + 1900) % 100 != 0 || (date.tm_year + 1900) % 400 == 0) && date.tm_mday > 29)
		throw ("Error: not a valid date => \"" + key + "\"");
	if (date.tm_mon == 1 && !((date.tm_year + 1900) % 4 == 0 && ((date.tm_year + 1900) % 100 != 0 || (date.tm_year + 1900) % 400 == 0)) && date.tm_mday > 28)
		throw ("Error: not a valid date => \"" + key + "\"");
}

static void	check_date(std::string&	key)
{
	if (key.empty() || key.length() > 10)
		throw("Error: not a valid date => \"" + key + "\"");
	if (key[4] != '-' || key[7] != '-')
		throw("Error: not a valid date => \"" + key + "\"");
	for (size_t	i = 0; i < 4; i++)
		if (!std::isdigit(key[i]))
			throw("Error: not a valid date => \"" + key + "\"");
	for (size_t	i = 5; i < 7; i++)
		if (!std::isdigit(key[i]))
			throw("Error: not a valid date => \"" + key + "\"");
	for (size_t	i = 8; i < 10; i++)
		if (!std::isdigit(key[i]))
			throw("Error: not a valid date => \"" + key + "\"");
	tm date;
	if (!strptime(key.c_str(), "%Y-%m-%d", &date))
		throw("Error: not a valid date => \"" + key + "\"");
	check_date_exceptions(date, key);
}

static void	check_value(std::string& value)
{
	bool point = false;
	if (value.empty() || value[value.length() - 1] == '.' || value[0] == '.')
		throw("Error: not a valid number => \"" + value + "\"");
	for (size_t i = 0; i < value.length(); i++)
	{
		if (!std::isdigit(value[i]) && value[i] != '.')
			throw("Error: not a valid number => \"" + value + "\"");
		if (value[i] == '.')
		{
			if (point == true)
				throw("Error: not valid a number => \"" + value + "\"");
			point = true;
		}
	}
}

void	parse_csv(std::map <std::string, std::string>& map)
{
	std::fstream 		database;
	
	std::string			string, key, value;

	database.open("data.csv");
	if (!database.is_open())
		throw ("Error: could not open database file.");
	std::getline(database, string);
	if (string.compare("date,exchange_rate"))
		throw ("Error: wrong database file header.");
	string.clear();
	while (std::getline(database, string))
	{
		std::stringstream	line;
		line << string;
		std::getline(line, key, ',');
		check_date(key);
		std::getline(line, value, '\n');
		check_value(value);
		map.insert(std::make_pair(key, value));
	}
}

static void	manage_exchange(std::string& key, std::string& value, std::map <std::string, std::string>& map)
{
	float result;
	float multi;

	result = std::atof(value.c_str());
	if (result > 1000)
		throw ("Error: not valid a number => \"" + value + "\"");
	std::string mulstr = static_cast<std::string>(map.lower_bound(key)->second);
	multi = atof(mulstr.c_str());
	result *= multi;
	std::cout << key << " => " << value << " = " << result << "\n";
}

void	execute_exchange(char *filename, std::map <std::string, std::string>& map)
{
	std::fstream		file;
	std::string			string, key, value;
	(void)map;
	file.open(filename);
	if (!file.is_open())
		throw ("Error: could not open file.");
	std::getline(file, string);
	if (string.compare("date | value"))
		throw ("Error: wrong file header.");
	string.clear();
	while (std::getline(file, string))
	{
		std::stringstream	line;
		line << string;
		try
		{
			std::getline(line, key, ' ');
			check_date(key);
			std::getline(line, value, ' ');
			if (value.length() != 1 || value[0] != '|')
				throw ("Error: wrong line format => \"" + string + "\"");
			std::getline(line, value, '\n');
			check_value(value);
			manage_exchange(key, value, map);
		}
		catch(const std::string e)
		{
			std::cerr << e << '\n';
		}
		catch(const char *e)
		{
			std::cerr << e << '\n';
		}
	}
}