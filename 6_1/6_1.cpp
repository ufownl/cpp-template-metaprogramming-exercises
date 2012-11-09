#include <boost/type_traits.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/copy_if.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/inserter.hpp>

using namespace boost;
using namespace boost::mpl;

struct binary_seq_tag
{
};

template <int N>
struct binary_seq
{
	typedef binary_seq_tag tag;
};

template <class _binary_seq, class _pos>
struct binary_seq_iterator
{
	typedef forward_iterator_tag category;
};

template <class _binary_seq, int _pos>
struct binary_seq_at;

template <int N>
struct binary_seq_at<binary_seq<N>, 0> : int_<N>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 1> : int_<N / 10>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 2> : int_<N / 100>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 3> : int_<N / 1000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 4> : int_<N / 10000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 5> : int_<N / 100000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 6> : int_<N / 1000000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 7> : int_<N / 10000000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 8> : int_<N / 100000000>
{
};

template <int N>
struct binary_seq_at<binary_seq<N>, 9> : int_<N / 1000000000>
{
};

namespace boost
{
	namespace mpl
	{

		template <>
		struct begin_impl<binary_seq_tag>
		{
			template <class _binary_seq>
			struct apply
			{
				typedef binary_seq_iterator<_binary_seq, int_<0> > type;
			};
		};

		template <>
		struct end_impl<binary_seq_tag>
		{
			template <class _binary_seq>
			struct apply
			{
				typedef binary_seq_iterator<_binary_seq, int_<10> > type;
			};
		};

		template <class _binary_seq, class _pos>
		struct next<binary_seq_iterator<_binary_seq, _pos> >
		{
			typedef binary_seq_iterator<_binary_seq, typename next<_pos>::type> type;
		};

		template <>
		struct at_impl<binary_seq_tag>
		{
			template <class _binary_seq, class _pos>
			struct apply : binary_seq_at<_binary_seq, _pos::value>
			{
			};
		};

		template <class _binary_seq, class _pos>
		struct deref<binary_seq_iterator<_binary_seq, _pos> > : at<_binary_seq, _pos>
		{
		};

	}
}

template <class T0, class T1>
struct convert_calc;

template <int a, int b>
struct convert_calc<int_<a>, int_<b> > : int_<a * 2 + b % 10>
{
	BOOST_STATIC_ASSERT((b % 10 < 2));
};

template <int N>
struct binary : reverse_copy_if<binary_seq<N>, greater<_1, int_<0> >, inserter<int_<0>, convert_calc<_1, _2> > >::type
{
	BOOST_STATIC_ASSERT((N >= 0));
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((binary<0>::value == 0));
	BOOST_STATIC_ASSERT((binary<1>::value == 1));
	BOOST_STATIC_ASSERT((binary<10>::value == 2));
	BOOST_STATIC_ASSERT((binary<11>::value == 3));
	BOOST_STATIC_ASSERT((binary<100>::value == 4));
	BOOST_STATIC_ASSERT((binary<101>::value == 5));
	BOOST_STATIC_ASSERT((binary<110>::value == 6));
	BOOST_STATIC_ASSERT((binary<111>::value == 7));
	return 0;
}
