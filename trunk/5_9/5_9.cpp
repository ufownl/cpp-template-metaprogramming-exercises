#include <boost/type_traits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/back.hpp>

using namespace boost;
using namespace boost::mpl;

template <int N>
struct fibonacci
{
	static const int value = fibonacci<N - 1>::value + fibonacci<N - 2>::value;
};

template <>
struct fibonacci<1>
{
	static const int value = 1;
};

template <>
struct fibonacci<0>
{
	static const int value = 0;
};

struct fibonacci_series_tag
{
};

template <int N>
struct fibonacci_series
{
	typedef fibonacci_series type;
	typedef fibonacci_series_tag tag;
	static const int size = N;
};

template <class _fibonacci_series, class _pos>
struct fibonacci_series_iterator
{
	typedef forward_iterator_tag category;
};

namespace boost
{
	namespace mpl
	{

		template <>
		struct begin_impl<fibonacci_series_tag>
		{
			template <class _fibonacci_series>
			struct apply
			{
				typedef fibonacci_series_iterator<_fibonacci_series, int_<0> > type;
			};
		};

		template <>
		struct end_impl<fibonacci_series_tag>
		{
			template <class _fibonacci_series>
			struct apply
			{
				typedef fibonacci_series_iterator<_fibonacci_series, int_<_fibonacci_series::size> > type;
			};
		};

		template <class _fibonacci_series, class _pos>
		struct next<fibonacci_series_iterator<_fibonacci_series, _pos> >
		{
			typedef fibonacci_series_iterator<_fibonacci_series, typename next<_pos>::type> type;
		};

		template <class _fibonacci_series, class _pos>
		struct prior<fibonacci_series_iterator<_fibonacci_series, _pos> >
		{
			typedef fibonacci_series_iterator<_fibonacci_series, typename prior<_pos>::type> type;
		};

		template <class _fibonacci_series, class _pos, class _offset>
		struct advance<fibonacci_series_iterator<_fibonacci_series, _pos>, _offset>
		{
			typedef fibonacci_series_iterator<_fibonacci_series, typename plus<_pos, _offset>::type> type;
		};

		template <class _fibonacci_series, class _pos>
		struct deref<fibonacci_series_iterator<_fibonacci_series, _pos> > : int_<fibonacci<_pos::value>::value>
		{
		};

	}
}

template <class _seq, class _it0, class _it1>
struct fibonacci_series_copy : fibonacci_series_copy<typename push_back<_seq, typename deref<_it0>::type>::type, typename next<_it0>::type, _it1>
{
};

template <class _seq, class _it>
struct fibonacci_series_copy<_seq, _it, _it> : _seq
{
};

template <class _seq, class _it0, class _it1>
struct fibonacci_series_reverse : fibonacci_series_reverse<typename push_back<_seq, typename deref<typename prior<_it1>::type>::type>::type, _it0, typename prior<_it1>::type>
{
};

template <class _seq, class _it>
struct fibonacci_series_reverse<_seq, _it, _it> : _seq
{
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((equal<fibonacci_series_copy<vector<>, begin<fibonacci_series<8> >::type, end<fibonacci_series<8> >::type >::type, vector<int_<0>, int_<1>, int_<1>, int_<2>, int_<3>, int_<5>, int_<8>, int_<13> > >::value));
	BOOST_STATIC_ASSERT((equal<fibonacci_series_reverse<vector<>, begin<fibonacci_series<8> >::type, end<fibonacci_series<8> >::type >::type, vector<int_<13>, int_<8>, int_<5>, int_<3>, int_<2>, int_<1>, int_<1>, int_<0> > >::value));
	typedef advance_c<begin<fibonacci_series<20> >::type, 6>::type p;
	BOOST_STATIC_ASSERT((deref<p>::type::value == 8));
	typedef advance_c<p, 4>::type q;
	BOOST_STATIC_ASSERT((deref<q>::type::value == 55));
	BOOST_STATIC_ASSERT((size<fibonacci_series<8> >::value == 8));
	BOOST_STATIC_ASSERT((back<fibonacci_series<8> >::type::value == 13));
	return 0;
}