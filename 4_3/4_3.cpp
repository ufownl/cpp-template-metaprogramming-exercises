#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/not_equal_to.hpp>
#include <boost/mpl/greater.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/multiplies.hpp>

using namespace boost;
using namespace boost::mpl;

template <class N, class Predicate>
struct next_if : if_<typename apply<Predicate, N>::type, typename next<N>::type, N>
{
};

template <class N, class Predicate>
struct eval_next_if : eval_if<typename apply<Predicate, N>::type, next<N>, identity<N> >
{
};

template <class N1, class N2>
struct formula
	: if_<
		not_equal_to<N1, N2>,
		typename if_<
			greater<N1, N2>,
			typename minus<N1, N2>::type,
			N1
		>::type,
		typename plus<
			N1,
			typename multiplies<
				N1,
				int_<2>
			>::type
		>::type
	>::type
{
};

template <class N1, class N2>
struct eval_formula
	: eval_if<
		not_equal_to<N1, N2>,
		if_<
			greater<N1, N2>,
			minus<N1, N2>,
			N1
		>,
		plus<
			N1,
			multiplies<
				N1,
				int_<2>
			>
		>
	>::type
{
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((is_same<next_if<int_<0>, equal_to<_1, int_<0> > >::type, eval_next_if<int_<0>, equal_to<_1, int_<0> > >::type>::value));
	BOOST_STATIC_ASSERT((is_same<next_if<int_<1>, equal_to<_1, int_<0> > >::type, eval_next_if<int_<1>, equal_to<_1, int_<0> > >::type>::value));
	BOOST_STATIC_ASSERT((is_same<formula<int_<2>, int_<1> >::type, eval_formula<int_<2>, int_<1> >::type>::value));
	BOOST_STATIC_ASSERT((is_same<formula<int_<1>, int_<1> >::type, eval_formula<int_<1>, int_<1> >::type>::value));
	return 0;
}