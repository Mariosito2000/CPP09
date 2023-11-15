#include "RPN.hpp"

int	operate(int	temp, int top, char op)
{
	if (op == '+')
		top += temp;
	else if (op == '-')
		top -= temp;
	else if (op == '*')
		top *= temp;
	else if (op == '/')
	{
		if (temp == 0)
			throw ("Error: cannot divide by zero");
		top /= temp;
	}

	return (top);
}

void	RPN(char *string)
{
	std::stack<int> nums;

	if (!string || !(std::strlen(string) % 2))
		throw ("Error");
	for (size_t	i = 0; i < std::strlen(string); i++)
	{
		if (!(i % 2))
		{
			if (std::strchr("+-*/", string[i]) != NULL && nums.size() > 1)
			{
				int	temp = nums.top();
				nums.pop();
				temp = operate(temp, nums.top(), string[i]);
				nums.pop();
				nums.push(temp);
			}
			else if (std::isdigit(string[i]))
				nums.push(string[i] - '0');
			else
				throw ("Error");
		}
		else if (string[i] != ' ')
			throw ("Error");
	}
	if (nums.size() > 1)
		throw ("Error");
	std::cout << nums.top() << "\n";
}