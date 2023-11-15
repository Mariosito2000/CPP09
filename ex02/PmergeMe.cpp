#include "PmergeMe.hpp"

/*---ARGS PARSING---*/
static int	arg_to_int(char * &arg, std::vector<int> &vector)
{
	if (!*arg)
		throw ("Error: invalid input");
	for(size_t i = 0; i < std::strlen(arg); i++)
		if (!(std::isdigit(arg[i])))
			throw ("Error: invalid input");
	long long int value = std::strtol(arg, NULL, 10);
	if (errno == ERANGE || value > INT_MAX || value < INT_MIN)
		throw ("Error: out of range value");
	for (size_t i = 0; i < vector.size(); i++)
		if (value == vector[i])
			throw ("Error: duplicated value");
	return (value);
}

/*---JACOBSTHAL---*/
static size_t	jacobsthal(size_t	n)
{
	if (n == 0)
        return (0);

    if (n == 1)
        return (1);

    return (jacobsthal(n - 1) + (2 * jacobsthal(n - 2)));
}

template <typename T>
static T get_jacobsthal_insertion_sequence(T &cont)
{
    T 		sequence;
	size_t	jacob_index = 3;

    while (jacobsthal(jacob_index) < cont.size())
	{
        sequence.push_back(jacobsthal(jacob_index));
        jacob_index += 1;
	}

	return (sequence);
}

/*---GET AN ITER FROM INDEX---*/
static std::list<int>::iterator iterator_index(std::list<int> &lst, size_t index)
{
	std::list<int>::iterator	it;
	if (index >= lst.size())
		std::cerr << "invalid index\n";
	if (index < ((lst.size() / 2) + 1))
	{
		it = lst.begin();
		for (size_t i = 0; i < index; i++)
			it++;
	}
	else
	{
		it = lst.end();
		for (size_t size = lst.size(); index < size; index++)
			it--;
	}
	return (it);
}

/*---STD::LIST---*/

/*---GET AN ITER FROM INDEX---*/
static std::list<std::pair<int, int> >::iterator iterator_index(std::list<std::pair<int, int> > &pair_lst, size_t index)
{
	std::list<std::pair<int, int> >::iterator	it;
	if (index >= pair_lst.size())
		std::cerr << "invalid index\n";
	if (index < ((pair_lst.size() / 2) + 1))
	{
		it = pair_lst.begin();
		for (size_t i = 0; i < index; i++)
			it++;
	}
	else
	{
		it = pair_lst.end();
		for (size_t size = pair_lst.size(); index < size; index++)
			it--;
	}
	return (it);
}

/*---ORDER PAIRS (BIG MEMBER)---*/
static void recursive_insertion_sort_list(std::list<std::pair<int, int> > &pair_lst, int n) 
{
	if (n <= 1)
		return;

	recursive_insertion_sort_list(pair_lst, n-1 );

	std::pair<int, int> last = *(iterator_index(pair_lst, n - 1));
	std::list<std::pair<int, int> >::iterator	it = iterator_index(pair_lst, n - 2);
	int	j = n - 2;

	while (j >= 0 && it->second > last.second)
	{
		*(++it) = *(it);
		--it;
		--it;
		j--;
	}
	*(++it) = last;
}

/*---JACOBSTHAL SORTED INSERTION ORDER---*/
std::list<int> build_insertion_lst(std::list<int> &js_lst, std::list<std::pair<int, int> > &pair_lst)
{
	std::list<int>								final_sequence;
	std::list<int>::iterator					js_iter = js_lst.begin();

	int	last_js = 0;

	if (js_lst.size() == 1)
	{
		final_sequence.push_back(2);
		final_sequence.push_back(1);
		if (pair_lst.size() == 4)
		{
			final_sequence.push_back(3);
			return(final_sequence);
		}
		else
			return (final_sequence);
	}
	while (js_iter != --(js_lst.end()))
	{
		final_sequence.push_back((*js_iter) - 1);
		for (int i = ((*js_iter) - 2); i > last_js; i--)
			final_sequence.push_back(i);
		last_js = *js_iter - 1;
		js_iter++;
	}
	final_sequence.push_back((*js_iter) - 1);
	for (int i = ((*js_iter) - 2); i > last_js; i--)
		final_sequence.push_back(i);
	for (int i = (*js_iter); i < (int)pair_lst.size(); i++)
		final_sequence.push_back(i);
	return (final_sequence);
}

/*---FIND A VALUE PARTNER---*/
static int	find_pair(std::list<int> &sorted_lst, int value)
{
	int	pos = 0;
	std::list<int>::iterator	ite = sorted_lst.end();
	for (std::list<int>::iterator it = sorted_lst.begin(); it != ite; it++)
	{
		if (*it == value)
			break;
		pos++;
	}
	return (pos);
}

static void	binary_search_insertion_lst(std::list<int> &sorted_lst, std::list<std::pair<int, int> > &pair_lst, std::list<int> &sorted_insertion_lst)
{
	for (size_t i = 0; i < sorted_insertion_lst.size(); i++)
	{
		int	left = 0;
		int	right = find_pair(sorted_lst, iterator_index(pair_lst, *(iterator_index(sorted_insertion_lst, i)))->second);
		int	value = iterator_index(pair_lst, *(iterator_index(sorted_insertion_lst, i)))->first;
		std::list<int>::iterator	iter;
		while (left != right)
		{
			iter = iterator_index(sorted_lst, (left + right) / 2);
			if (value > *iter)
				left = (left + right + 1) / 2;
			else
				right = (left + right - 1) / 2;
		}
		iter = iterator_index(sorted_lst, (left + right) / 2);
		if (*iter < value)
			sorted_lst.insert(++iter, value);
		else
			sorted_lst.insert(iter, value);
	}
}

static void	extra_binary_search_lst(std::list<int> &sorted_lst, int	extra)
{
	int	left = 0;
	int	right = sorted_lst.size() - 1;
	std::list<int>::iterator	iter;
	while (left != right)
	{
		iter = iterator_index(sorted_lst, (left + right) / 2);
		if (extra > *iter)
			left = (left + right + 1) / 2;
		else
			right = (left + right - 1) / 2;
	}
	iter = iterator_index(sorted_lst, (left + right) / 2);
	if (*iter < extra)
		sorted_lst.insert(++iter, extra);
	else
		sorted_lst.insert(iter, extra);
}

static long int	sort_list(std::list<int> &lst)
{
	struct timeval start;
	gettimeofday(&start, NULL);

	bool							odd = false;
	int								extra;
	std::list<std::pair<int, int> >	pair_lst;
	std::list<int>					sorted_lst;

	/*---CHECK ODD---*/
	if (lst.size() % 2)
	{
		odd = true;
		extra = lst.back();
		lst.pop_back();
	}

	/*---CREATE PAIRS---*/
	if (lst.size() > 1)
	{
		for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		{
			int		pair[2] = {*it, *(++it)};
			if (pair[0] > pair[1])
			{
				int	temp = pair[0];
				pair[0] = pair[1];
				pair[1] = temp;
			}
			pair_lst.push_back(std::make_pair(pair[0], pair[1]));
		}
	}

	if (pair_lst.size() != 0)
	{
		/*---SORT PAIRS---*/
		recursive_insertion_sort_list(pair_lst, (int)pair_lst.size());

		/*---SORTED BIGS---*/
		for (std::list<std::pair<int, int> >::iterator	pit = pair_lst.begin(); pit != pair_lst.end(); ++pit)
			sorted_lst.push_back(pit->second);
		sorted_lst.push_front(pair_lst.begin()->first);

		/*---INSERT SMALLS---*/
		std::list<int>	sorted_insertion_lst;
		if (pair_lst.size() > 1)
		{
			std::list<int> js_lst = get_jacobsthal_insertion_sequence(sorted_lst);
			if (js_lst.size() > 0)
				sorted_insertion_lst = build_insertion_lst(js_lst, pair_lst);
			else
			{
				if (pair_lst.size() == 2)
					sorted_insertion_lst.push_back(1);
				else
				{
					sorted_insertion_lst.push_back(1);
					sorted_insertion_lst.push_back(2);
				}
			}
		}
		binary_search_insertion_lst(sorted_lst, pair_lst, sorted_insertion_lst);
	}

	/*---INSERT EXTRA NUMBER---*/
	if (odd && sorted_lst.size())
		extra_binary_search_lst(sorted_lst, extra);
	else if (odd)
		sorted_lst.push_back(extra);

	lst = sorted_lst;

	struct timeval end;
	gettimeofday(&end, NULL);
	return (end.tv_usec - start.tv_usec);
}

/*---STD::VECTOR---*/

static void recursive_insertion_sort_vec(std::vector<std::pair<int, int> > &pair_vec, int n)
{
	if (n <= 1)
		return;

	recursive_insertion_sort_vec(pair_vec, n - 1 );

	std::pair<int, int> last = pair_vec[n - 1];
	int	j = n - 2;

	while (j >= 0 && pair_vec[j].second > last.second)
	{
		pair_vec[j + 1] = pair_vec[j];
		j--;
	}
	pair_vec[j + 1] = last;
}

std::vector<int> build_insertion_vec(std::vector<int> &js_vec, std::vector<std::pair<int, int> > &pair_vec)
{
	std::vector<int>			final_sequence;
	int							js_iter = 0;

	int	last_js = 0;

	if (js_vec.size() == 1)
	{
		final_sequence.push_back(2);
		final_sequence.push_back(1);
		if (pair_vec.size() == 4)
		{
			final_sequence.push_back(3);
			return(final_sequence);
		}
		else
			return (final_sequence);
	}
	while (js_iter < (int)js_vec.size() - 1)
	{
		final_sequence.push_back((js_vec[js_iter]) - 1);
		for (int i = ((js_vec[js_iter]) - 2); i > last_js; i--)
			final_sequence.push_back(i);
		last_js = js_vec[js_iter] - 1;
		js_iter++;
	}
	final_sequence.push_back((js_vec[js_iter]) - 1);
	for (int i = ((js_vec[js_iter]) - 2); i > last_js; i--)
		final_sequence.push_back(i);
	for (int i = (js_vec[js_iter]); i < (int)pair_vec.size(); i++)
		final_sequence.push_back(i);
	return (final_sequence);
}

static std::vector<int>::iterator index_iterator(std::vector<int> &sorted_vec, int index)
{
	std::vector<int>::iterator it = sorted_vec.begin();
	for (int i = 0; i < index; i++)
		it++;
	return (it);
}

static void	binary_search_insertion_vec(std::vector<int> &sorted_vec, std::vector<std::pair<int, int> > &pair_vec, std::vector<int> &sorted_insertion_vec)
{
	for (size_t i = 0; i < sorted_insertion_vec.size(); i++)
	{
		int	left = 0;
		int	right;
		for (int b = 0; pair_vec[sorted_insertion_vec[i]].second != sorted_vec[b]; b++)
			if (pair_vec[i].second != sorted_vec[b + 1])
				right = b + 1;
		int	value = pair_vec[sorted_insertion_vec[i]].first;
		while (left != right)
		{
			if (value > sorted_vec[(left + right) / 2])
				left = (left + right + 1) / 2;
			else
				right = (left + right - 1) / 2;
		}
		if (sorted_vec[(left + right) / 2] < value)
			sorted_vec.insert(index_iterator(sorted_vec, left + 1), value);
		else
			sorted_vec.insert(index_iterator(sorted_vec, left), value);
	}
}

static void	extra_binary_search_vec(std::vector<int> &sorted_vec, int extra)
{
	int	left = 0;
	int	right = sorted_vec.size() - 1;
	while (left != right)
	{
		if (extra > sorted_vec[(left + right) / 2])
			left = (left + right + 1) / 2;
		else
			right = (left + right - 1) / 2;
	}
	if (sorted_vec[(left + right) / 2] < extra)
		sorted_vec.insert(index_iterator(sorted_vec, ((left + right) / 2) + 1), extra);
	else
		sorted_vec.insert(index_iterator(sorted_vec, (left + right) / 2), extra);
}

static long int	sort_vector(std::vector<int> &vector)
{
	struct timeval start;
	gettimeofday(&start, NULL);

	bool								odd = false;
	int									extra;
	std::vector<std::pair<int, int> >	pair_vec;
	std::vector<int>					sorted_vec;
	
	/*---CHECK ODD---*/
	if (vector.size() % 2)
	{
		odd = true;
		extra = vector.back();
		vector.pop_back();
	}

	/*---CREATE PAIRS---*/
	if (vector.size() > 1)
	{
		for (size_t i = 0; i < vector.size(); ++(++i))
		{
			int		pair[2] = {vector[i], vector[i + 1]};
			if (pair[0] > pair[1])
			{
				int	temp = pair[0];
				pair[0] = pair[1];
				pair[1] = temp;
			}
			pair_vec.push_back(std::make_pair(pair[0], pair[1]));
		}
	}

	if (pair_vec.size() != 0)
	{
		/*---SORT PAIRS---*/
		recursive_insertion_sort_vec(pair_vec, (int)pair_vec.size());

		/*---SORTED LIST---*/
		for (size_t	i = 0; i < pair_vec.size(); i++)
			sorted_vec.push_back(pair_vec[i].second);
		sorted_vec.insert(sorted_vec.begin(), pair_vec[0].first);

		/*---INSERT SMALLS---*/
		std::vector<int>	sorted_insertion_vec;
		if (pair_vec.size() > 1)
		{
			std::vector<int> js_vec = get_jacobsthal_insertion_sequence(sorted_vec);
			if (js_vec.size() > 0)
				sorted_insertion_vec = build_insertion_vec(js_vec, pair_vec);
			else
			{
				if (pair_vec.size() == 2)
					sorted_insertion_vec.push_back(1);
				else
				{
					sorted_insertion_vec.push_back(1);
					sorted_insertion_vec.push_back(2);
				}
			}
		}
		binary_search_insertion_vec(sorted_vec, pair_vec, sorted_insertion_vec);
	}

	/*---INSERT EXTRA NUMBER---*/
	if (odd && sorted_vec.size())
		extra_binary_search_vec(sorted_vec, extra);
	else if (odd)
		sorted_vec.push_back(extra);

	vector = sorted_vec;

	struct timeval end;
	gettimeofday(&end, NULL);
	return (end.tv_usec - start.tv_usec);
}

static void	print_result(std::vector<int>	&vector, long int lst_time, long int vector_time)
{
	std::cout << "After: ";
	for (size_t i = 0; i < vector.size(); i++)
		std::cout << " " << vector[i];
	std::cout << "\nTime to process a range of " << vector.size() << " elements with std::list<int> : " << lst_time << " µsec";
	std::cout << "\nTime to process a range of " << vector.size() << " elements with std::vector<int> : " << vector_time << " µsec\n";
}

void	PmergeMe(int argc, char **argv)
{
	std::list<int>				lst;
	long int					lst_time;

	std::vector<int>			vector;
	long int					vector_time;

	int							value;

	for (int i = 1; i < argc; i++)
	{
		value = arg_to_int(argv[i], vector);
		lst.push_back(value);
		vector.push_back(value);
	}
	std::cout << "Before: ";
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); it++)
		std::cout << " " << *it;
	std::cout << "\n";

	lst_time = sort_list(lst);

	vector_time = sort_vector(vector);

	print_result(vector, lst_time, vector_time);
}