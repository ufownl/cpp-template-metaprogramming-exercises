#include <boost/type_traits.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>

using namespace boost;
using namespace boost::mpl;

template <class T>
struct remove_array;

template <class T, int N>
struct remove_array<T[N]>
{
	typedef T type;
};

template <class T>
struct array_element_count;

template <class T, int N>
struct array_element_count<T[N]> : int_<N>
{
};

template <class _seq, class T, bool _array>
struct dimensions_impl : dimensions_impl<typename push_front<_seq, typename array_element_count<T>::type>::type, typename remove_array<T>::type, is_array<typename remove_array<T>::type>::value>
{
};

template <class _seq, class T>
struct dimensions_impl<_seq, T, false> : _seq
{
};

struct dimensions_tag
{
};

template <class T>
struct dimensions : dimensions_impl<deque<>, T, is_array<T>::value>
{
	typedef dimensions_tag tag;
};

namespace boost
{
	namespace mpl
	{

		template <>
		struct size_impl<dimensions_tag>
		{
			template <class _dimensions>
			struct apply : size<typename _dimensions::type>
			{
			};
		};

		template <>
		struct at_impl<dimensions_tag>
		{
			template <class _dimensions, class _pos>
			struct apply : at<typename _dimensions::type, _pos>
			{
			};
		};

	}
}

int main(int argc, char *argv[])
{
	typedef dimensions<char [10][5][2][4]> seq;
	BOOST_STATIC_ASSERT((size<seq>::value == 4));
	BOOST_STATIC_ASSERT((at_c<seq, 0>::type::value == 4));
	BOOST_STATIC_ASSERT((at_c<seq, 1>::type::value == 2));
	BOOST_STATIC_ASSERT((at_c<seq, 2>::type::value == 5));
	BOOST_STATIC_ASSERT((at_c<seq, 3>::type::value == 10));
	return 0;
}