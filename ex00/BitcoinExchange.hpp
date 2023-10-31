#pragma once
#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

void	parse_csv(std::map <std::string, std::string>& map);
void	execute_exchange(char *filename, std::map <std::string, std::string>& map);

#endif