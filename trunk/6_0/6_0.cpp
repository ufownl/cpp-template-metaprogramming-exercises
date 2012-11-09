#include <boost/type_traits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/vector.hpp>

using namespace boost;
using namespace boost::mpl;

typedef char max_type[0x7FFFFFFF];

template <class T0, class T1>
struct min : eval_if<bool_<sizeof(T0) < sizeof(T1)>, identity<T0>, identity<T1> >
{
};

template <class _seq>
struct smallest : copy<_seq, inserter<max_type, min<_1, _2> > >
{
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((is_same<smallest<vector<int[2], char, double&> >::type, char>::value));
	return 0;
}