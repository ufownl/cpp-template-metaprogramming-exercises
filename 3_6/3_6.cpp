#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <boost/mpl/apply.hpp>

#include <boost/mpl/multiplies.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>

using namespace boost;
using namespace boost::mpl;

template <class F, class T>
struct twice : apply<F, typename apply<F, T>::type>
{
};

int main(int argc, char *argv[])
{
	typedef apply<add_pointer<_1>, apply<add_pointer<_1>, apply<add_pointer<_1>, apply<add_pointer<_1>, int>::type>::type>::type>::type type;
	BOOST_STATIC_ASSERT((is_same<twice<add_pointer<_1>, twice<add_pointer<_1>, int>::type>::type, type>::value));
	return 0;
}
