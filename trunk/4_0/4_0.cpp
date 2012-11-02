#include <boost/static_assert.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>

using namespace boost;
using namespace boost::mpl;

template <bool val>
struct abort_
{
	BOOST_STATIC_ASSERT(false);
	typedef abort_<val> type;
	static const bool value = val;
};

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

	BOOST_STATIC_ASSERT((or_<true_, abort_<true> >::value));
	BOOST_STATIC_ASSERT((or_<true_, abort_<false> >::value));
	BOOST_STATIC_ASSERT((!and_<false_, abort_<true> >::value));
	BOOST_STATIC_ASSERT((!and_<false_, abort_<false> >::value));

	return 0;
}