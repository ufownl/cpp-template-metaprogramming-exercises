#include <boost/type_traits.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/minus.hpp>
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

template <class _seq0, class _seq1>
struct crossproduct_view
	: transform<
		typename transform<
			typename permutation_view<vector_c<int, 1, 2, 0>, _seq0>::type,
			typename permutation_view<vector_c<int, 2, 0, 1>, _seq1>::type,
			multiplies<_1, _2>,
			back_inserter<vector<> >
		>::type,
		typename transform<
			typename permutation_view<vector_c<int, 1, 2, 0>, _seq1>::type,
			typename permutation_view<vector_c<int, 2, 0, 1>, _seq0>::type,
			multiplies<_1, _2>,
			back_inserter<vector<> >
		>::type,
		minus<_1, _2>
	>
{
};

int main(int argc, char *argv[])
{
	typedef vector_c<int, 1, 2, 3> v0;
	typedef vector_c<int, 3, 2, 1> v1;
	BOOST_STATIC_ASSERT((equal<crossproduct_view<v0, v1>::type, vector_c<int, 2 * 1 - 2 * 3, 3 * 3 - 1 * 1, 1 * 2 - 3 * 2> >::value));
	return 0;
}