#include <boost/type_traits.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/equal.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _seq, class _size, class _it0, class _it1>
struct double_first_half_impl
	: eval_if<
		less<typename minus<_size, typename distance<_it0, _it1>::type>::type, typename divides<_size, int_<2> >::type>,
		double_first_half_impl<typename push_back<_seq, typename multiplies<typename deref<_it0>::type, int_<2> >::type>::type, _size, typename next<_it0>::type, _it1>,
		double_first_half_impl<typename push_back<_seq, typename deref<_it0>::type>::type, _size, typename next<_it0>::type, _it1>
	>
{
};

template <class _seq, class _size, class _it>
struct double_first_half_impl<_seq, _size, _it, _it> : _seq
{
};

template <class _seq>
struct double_first_half : double_first_half_impl<typename clear<_seq>::type, typename size<_seq>::type, typename begin<_seq>::type, typename end<_seq>::type>
{
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((equal<double_first_half<vector_c<int, 1, 2, 3, 4> >::type, vector_c<int, 2, 4, 3, 4> >::value));
	BOOST_STATIC_ASSERT((equal<double_first_half<vector_c<int, 2, 4, 3, 4> >::type, vector_c<int, 4, 8, 3, 4> >::value));
	BOOST_STATIC_ASSERT((equal<double_first_half<vector_c<long, 5, 4, 3, 2, 1> >::type, vector_c<long, 10, 8, 3, 2, 1> >::value));
	return 0;
}