#include <boost/type_traits.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/equal.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _iter>
struct reverse_iterator
{
	typedef typename _iter::category category;
	typedef typename prior<_iter>::type base;
	typedef typename deref<base>::type type;
};

namespace boost
{
	namespace mpl
	{

		template <class _iter>
		struct next<reverse_iterator<_iter> >
		{
			typedef reverse_iterator<typename prior<_iter>::type> type;
		};

		template <class _iter>
		struct prior<reverse_iterator<_iter> >
		{
			typedef reverse_iterator<typename next<_iter>::type> type;
		};

		template <class _iter, class _offset>
		struct advance<reverse_iterator<_iter>, _offset>
		{
			typedef reverse_iterator<typename advance<_iter, typename minus<int_<0>, _offset>::type>::type> type;
		};

		template <class _seq>
		struct rbegin
		{
			typedef reverse_iterator<typename end<_seq>::type> type;
		};

		template <class _seq>
		struct rend
		{
			typedef reverse_iterator<typename begin<_seq>::type> type;
		};

	}
}

template <class _seq>
struct reverse_view : iterator_range<typename rbegin<_seq>::type, typename rend<_seq>::type>
{
};

int main(int argc, char *argv[])
{
	typedef vector<char, int, long> v;
	BOOST_STATIC_ASSERT((is_same<deref<advance<rbegin<v>::type, int_<2> >::type>::type, char>::value));
	BOOST_STATIC_ASSERT((is_same<deref<prior<advance<rbegin<v>::type, int_<2> >::type>::type>::type, int>::value));
	BOOST_STATIC_ASSERT((equal<reverse_view<v>::type, vector<long, int, char> >::value));
	return 0;
}