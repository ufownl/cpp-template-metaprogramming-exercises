#include <boost/type_traits.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/iterator_range.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/range_c.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _seq, class _pos>
struct rotate_view : joint_view<iterator_range<_pos, typename end<_seq>::type>, iterator_range<typename begin<_seq>::type, _pos> >
{
};

int main(int argc, char *argv[])
{
	typedef vector_c<int, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4> v;
	typedef rotate_view<v, advance_c<begin<v>::type, 5>::type> view;
	BOOST_STATIC_ASSERT((equal<view, range_c<int, 0, 10> >::value));
	return 0;
}