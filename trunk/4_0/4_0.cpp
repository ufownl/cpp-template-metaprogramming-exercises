#include <boost/static_assert.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>

using namespace boost;
using namespace boost::mpl;

struct nil;

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((or_<true_, true_ >::value));
	BOOST_STATIC_ASSERT((or_<false_, true_ >::value));
	BOOST_STATIC_ASSERT((or_<true_, false_ >::value));
	BOOST_STATIC_ASSERT((!or_<false_, false_ >::value));

	BOOST_STATIC_ASSERT((and_<true_, true_ >::value));
	BOOST_STATIC_ASSERT((!and_<false_, true_ >::value));
	BOOST_STATIC_ASSERT((!and_<true_, false_ >::value));
	BOOST_STATIC_ASSERT((!and_<false_, false_ >::value));

	BOOST_STATIC_ASSERT((or_<true_, nil>::value));
	BOOST_STATIC_ASSERT((or_<true_, nil>::value));
	BOOST_STATIC_ASSERT((!and_<false_, nil>::value));
	BOOST_STATIC_ASSERT((!and_<false_, nil>::value));

	return 0;
}
