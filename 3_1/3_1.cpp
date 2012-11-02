#include <boost/static_assert.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/transform.hpp>

using namespace boost;
using namespace boost::mpl;

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((equal<transform<vector_c<int, 1, 2, 3>, vector_c<int, 1, 1, 1>, plus<_1, _2> >::type, vector_c<int, 2, 3, 4> >::value));
	return 0;
}