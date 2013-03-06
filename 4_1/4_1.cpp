#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>

using namespace boost;
using namespace boost::mpl;

template <class T1, class T2>
struct logical_or : true_
{
};

template <>
struct logical_or<false_, false_> : false_
{
};

template <class T1, class T2>
struct logical_and : false_
{
};

template <>
struct logical_and<true_, true_> : true_
{
};

struct nil;

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((logical_or<true_, true_ >::value));
	BOOST_STATIC_ASSERT((logical_or<false_, true_ >::value));
	BOOST_STATIC_ASSERT((logical_or<true_, false_ >::value));
	BOOST_STATIC_ASSERT((!logical_or<false_, false_ >::value));

	BOOST_STATIC_ASSERT((logical_and<true_, true_ >::value));
	BOOST_STATIC_ASSERT((!logical_and<false_, true_ >::value));
	BOOST_STATIC_ASSERT((!logical_and<true_, false_ >::value));
	BOOST_STATIC_ASSERT((!logical_and<false_, false_ >::value));

	BOOST_STATIC_ASSERT((logical_or<true_, nil>::value));
	BOOST_STATIC_ASSERT((logical_or<true_, nil>::value));
	BOOST_STATIC_ASSERT((!logical_and<false_, nil>::value));
	BOOST_STATIC_ASSERT((!logical_and<false_, nil>::value));

	return 0;
}
