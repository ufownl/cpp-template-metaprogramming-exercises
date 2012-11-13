#include <boost/type_traits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/print.hpp>

using namespace boost;
using namespace boost::mpl;

template <int N, int I>
struct is_prime_impl
{
	static const bool value = N % I != 0 && is_prime_impl<N, I - 1>::value;
};

template <int N>
struct is_prime_impl<N, 2>
{
	static const bool value = N % 2 != 0;
};

template <int I>
struct is_prime_impl<2, I>
{
	static const bool value = true;
};

template <int I>
struct is_prime_impl<1, I>
{
	static const bool value = false;
};

template <int I>
struct is_prime_impl<0, I>
{
	static const bool value = false;
};

template <class T>
struct is_prime : bool_<is_prime_impl<T::value, T::value - 1>::value>
{
};

template <int N>
struct print_prime
	: copy_if<
		range_c<int, 2, N>,
		is_prime<_1>,
		inserter<int_<0>, print<_2> >
	>
{
};

int main(int argc, char *argv[])
{
	typedef print_prime<100>::type type;
	return 0;
}