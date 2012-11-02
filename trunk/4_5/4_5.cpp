#include <stdio.h>

#include <vector>

#include <boost/type_traits.hpp>
#include <boost/mpl/if.hpp>
#include <algorithm>

using namespace boost;
using namespace boost::mpl;

template <class _container>
struct container_iterator : if_<is_const<_container>, typename _container::const_iterator, typename _container::iterator>
{
};

template <class _container, class _value>
typename container_iterator<_container>::type container_find(_container &c, const _value &v)
{
	return std::find(c.begin(), c.end(), v);
}

int main(int argc, char *argv[])
{
	std::vector<int> vec;

	for (int i = 0; i < 10; ++i)
	{
		vec.push_back(i);
	}

	const std::vector<int> const_vec(vec.begin(), vec.end());

	std::vector<int>::iterator iter = container_find(vec, 8);
	std::vector<int>::const_iterator const_iter = container_find(const_vec, 8);

	printf("%d %d\n", *iter, *const_iter);

	return 0;
}