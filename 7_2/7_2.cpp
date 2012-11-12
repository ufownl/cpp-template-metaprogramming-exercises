#include <boost/type_traits.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/int.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _iter_seq>
struct zip_iterator
{
	typedef random_access_iterator_tag category;
	typedef typename transform<_iter_seq, deref<_1> >::type type;
	typedef _iter_seq base;
};

namespace boost
{
	namespace mpl
	{

		template <class _iter_seq>
		struct next<zip_iterator<_iter_seq> >
		{
			typedef zip_iterator<typename transform<_iter_seq, next<_1> >::type> type;
		};

		template <class _iter_seq>
		struct prior<zip_iterator<_iter_seq> >
		{
			typedef zip_iterator<typename transform<_iter_seq, prior<_1> >::type> type;
		};

		template <class _iter_seq, class _offset>
		struct advance<zip_iterator<_iter_seq>, _offset>
		{
			typedef zip_iterator<typename transform<_iter_seq, advance<_1, _offset> >::type> type;
		};

	}
}

template <class _seq>
struct zip_view : iterator_range<zip_iterator<typename transform<_seq, begin<_1> >::type>, zip_iterator<typename transform<_seq, end<_1> >::type> >
{
};

int main(int argc, char *argv[])
{
	typedef vector<int, float, long> v0;
	typedef vector<char, double, short> v1;
	typedef vector<long, short, float> v2;
	BOOST_STATIC_ASSERT((is_same<copy<zip_view<vector<v0, v1, v2> >, back_inserter<vector<> > >::type, vector3<vector3<int, char, long>, vector3<float, double, short>, vector3<long, short, float> > >::value));
	BOOST_STATIC_ASSERT((is_same<begin<zip_view<vector<v0, v1, v2> > >::type, prior<prior<prior<end<zip_view<vector<v0, v1, v2> > >::type>::type>::type>::type>::value));
	BOOST_STATIC_ASSERT((is_same<advance<begin<zip_view<vector<v0, v1, v2> > >::type, int_<3> >::type, end<zip_view<vector<v0, v1, v2> > >::type>::value));
	return 0;
}