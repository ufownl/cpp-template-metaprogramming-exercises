#include <boost/type_traits.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/deque.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/long.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector_c.hpp>

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

template <class _dimensions, class _pos>
struct dimensions_iterator
{
	typedef bidirectional_iterator_tag category;
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

		template <class _dimensions, class _pos>
		struct next<dimensions_iterator<_dimensions, _pos> >
		{
			typedef dimensions_iterator<_dimensions, typename next<_pos>::type> type;
		};

		template <class _dimensions, class _pos>
		struct prior<dimensions_iterator<_dimensions, _pos> >
		{
			typedef dimensions_iterator<_dimensions, typename prior<_pos>::type> type;
		};

		template <class _dimensions, class _pos>
		struct deref<dimensions_iterator<_dimensions, _pos> > : at<typename _dimensions::type, _pos>
		{
		};

		template <>
		struct begin_impl<dimensions_tag>
		{
			template <class _dimensions>
			struct apply
			{
				typedef dimensions_iterator<_dimensions, long_<0> > type;
			};
		};

		template <>
		struct end_impl<dimensions_tag>
		{
			template <class _dimensions>
			struct apply
			{
				typedef dimensions_iterator<_dimensions, typename size<typename _dimensions::type>::type> type;
			};
		};

		template <>
		struct push_back_impl<dimensions_tag>
		{
			template <class _dimensions, class T>
			struct apply : push_back<typename _dimensions::type, T>
			{
			};
		};

		template <>
		struct pop_back_impl<dimensions_tag>
		{
			template <class _dimensions>
			struct apply : pop_back<typename _dimensions::type>
			{
			};
		};

	}
}

template <class _seq, class _it0, class _it1>
struct dimensions_copy : dimensions_copy<typename push_back<_seq, typename deref<_it0>::type>::type, typename next<_it0>::type, _it1>
{
};

template <class _seq, class _it>
struct dimensions_copy<_seq, _it, _it> : _seq
{
};

template <class _seq, class _it0, class _it1>
struct dimensions_reverse : dimensions_reverse<typename push_back<_seq, typename deref<typename prior<_it1>::type>::type>::type, _it0, typename prior<_it1>::type>
{
};

template <class _seq, class _it>
struct dimensions_reverse<_seq, _it, _it> : _seq
{
};

int main(int argc, char *argv[])
{
	typedef dimensions<char [10][5][2][4]> seq;
	BOOST_STATIC_ASSERT((size<seq>::value == 4));
	BOOST_STATIC_ASSERT((at_c<seq, 0>::type::value == 4));
	BOOST_STATIC_ASSERT((at_c<seq, 1>::type::value == 2));
	BOOST_STATIC_ASSERT((at_c<seq, 2>::type::value == 5));
	BOOST_STATIC_ASSERT((at_c<seq, 3>::type::value == 10));
	BOOST_STATIC_ASSERT((equal<dimensions_copy<vector<>, begin<seq>::type, end<seq>::type>::type, vector<int_<4>, int_<2>, int_<5>, int_<10> > >::value));
	BOOST_STATIC_ASSERT((equal<dimensions_reverse<vector<>, begin<seq>::type, end<seq>::type>::type, vector<int_<10>, int_<5>, int_<2>, int_<4> > >::value));
	BOOST_STATIC_ASSERT((equal<push_back<seq, int_<20> >::type, vector<int_<4>, int_<2>, int_<5>, int_<10>, int_<20> > >::value));
	BOOST_STATIC_ASSERT((equal<pop_back<seq>::type, vector<int_<4>, int_<2>, int_<5> > >::value));
	return 0;
}