#include <boost/type_traits.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/list_c.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/equal.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _seq, class _index_iter>
struct permutation_iterator
{
	typedef typename _index_iter::category category;
	typedef typename advance<typename begin<_seq>::type, typename deref<_index_iter>::type>::type base;
	typedef typename deref<base>::type type;
};

namespace boost
{
	namespace mpl
	{

		template <class _seq, class _index_iter>
		struct next<permutation_iterator<_seq, _index_iter> >
		{
			typedef permutation_iterator<_seq, typename next<_index_iter>::type> type;
		};

		template <class _seq, class _index_iter>
		struct prior<permutation_iterator<_seq, _index_iter> >
		{
			typedef permutation_iterator<_seq, typename prior<_index_iter>::type> type;
		};

		template <class _seq, class _index_iter, class _offset>
		struct advance<permutation_iterator<_seq, _index_iter>, _offset>
		{
			typedef permutation_iterator<_seq, typename advance<_index_iter, _offset>::type> type;
		};

	}
}

template <class _index_seq, class _seq>
struct permutation_view : iterator_range<permutation_iterator<_seq, typename begin<_index_seq>::type>, permutation_iterator<_seq, typename end<_index_seq>::type> >
{
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((equal<permutation_view<list_c<int, 2, 1, 3, 0, 2>, vector_c<int, 11, 22, 33, 44> >::type, vector_c<int, 33, 22, 44, 11, 33> >::value));
	return 0;
}