#include <boost/type_traits.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/int.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _seq, class _index_iter>
struct permutation_iterator
{
	typedef forward_iterator_tag category;
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

	}
}

int main(int argc, char *argv[])
{
	typedef vector_c<int, 2, 0, 1> index;
	typedef vector_c<int, 10, 100, 1000> seq;
	typedef permutation_iterator<seq, begin<index>::type> iter;
	BOOST_STATIC_ASSERT((equal_to<deref<iter>::type, int_<1000> >::value));
	BOOST_STATIC_ASSERT((equal_to<deref<next<iter>::type>::type, int_<10> >::value));
	BOOST_STATIC_ASSERT((equal_to<deref<next<next<iter>::type>::type>::type, int_<100> >::value));
	return 0;
}