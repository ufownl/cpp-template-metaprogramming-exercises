#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/eval_if.hpp>
#include <vector>
#include <list>
#include <string.h>

using namespace boost;
using namespace boost::mpl;

template <class _iter>
typename enable_if<
	is_arithmetic<
		typename iterator_value<_iter>::type
	>,
	typename iterator_value<_iter>::type
>::type sum(_iter start, _iter end)
{
	typename iterator_value<_iter>::type ret(0);

	for ( ; start != end; ++start)
	{
		ret += *start;
	}

	return ret;
}

template <class _iter>
struct inner_value;

template <class _iter, bool _is_arithmetic>
struct inner_value_impl : iterator_value<_iter>
{
};

template <class _iter>
struct inner_value_impl<_iter, false> : inner_value<typename iterator_value<_iter>::type::iterator>
{
};

template <class _iter>
struct inner_value : inner_value_impl<_iter, is_arithmetic<typename iterator_value<_iter>::type>::value>
{
};

template <class _iter>
typename lazy_disable_if<
	is_arithmetic<
		typename iterator_value<_iter>::type
	>,
	inner_value<_iter>
>::type sum(_iter start, _iter end)
{
	typename inner_value<_iter>::type ret(0);

	for ( ; start != end; ++start)
	{
		ret += sum(start->begin(), start->end());
	}

	return ret;
}

int main(int argc, char *argv[])
{
	std::list<int> l0(10, 1);
	std::list<std::list<int> > l1(10, l0);
	std::vector<std::list<std::list<int> > > v(10, l1);
	std::vector<std::list<std::list<int> > > a[5] = {v, v, v, v, v};
	int s = sum(a, a + 5);

	printf("%d\n", s);

	return 0;
}
