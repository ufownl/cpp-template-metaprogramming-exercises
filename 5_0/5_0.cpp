#include <boost/type_traits.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/prior.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/push_back.hpp>

using namespace boost;
using namespace boost::mpl;

struct none
{
};

struct tiny_tag
{
};

template <class T0 = none, class T1 = none, class T2 = none>
struct tiny
{
	typedef tiny_tag tag;
	typedef tiny type;
	typedef T0 t0;
	typedef T1 t1;
	typedef T2 t2;
};

template <class _tiny, class _pos>
struct tiny_iterator
{
	typedef random_access_iterator_tag category;
};

template <class _tiny, int _index>
struct tiny_at;

template <class _tiny>
struct tiny_at<_tiny, 0>
{
	typedef typename _tiny::t0 type;
};

template <class _tiny>
struct tiny_at<_tiny, 1>
{
	typedef typename _tiny::t1 type;
};

template <class _tiny>
struct tiny_at<_tiny, 2>
{
	typedef typename _tiny::t2 type;
};

template <class T0, class T1, class T2>
struct tiny_size : int_<3>
{
};

template <class T0, class T1>
struct tiny_size<T0, T1, none> : int_<2>
{
};

template <class T0>
struct tiny_size<T0, none, none> : int_<1>
{
};

template <>
struct tiny_size<none, none, none> : int_<0>
{
};

template <class _tiny, class T, int _size>
struct tiny_push_back;

template <class _tiny, class T>
struct tiny_push_back<_tiny, T, 0> : tiny<T, none, none>
{
};

template <class _tiny, class T>
struct tiny_push_back<_tiny, T, 1> : tiny<typename _tiny::t0, T, none>
{
};

template <class _tiny, class T>
struct tiny_push_back<_tiny, T, 2> : tiny<typename _tiny::t0, typename _tiny::t1, T>
{
};

namespace boost
{
	namespace mpl
	{

		template <class _tiny, class _pos>
		struct next<tiny_iterator<_tiny, _pos> >
		{
			typedef tiny_iterator<_tiny, typename next<_pos>::type> type;
		};

		template <class _tiny, class _pos>
		struct prior<tiny_iterator<_tiny, _pos> >
		{
			typedef tiny_iterator<_tiny, typename prior<_pos>::type> type;
		};

		template <>
		struct at_impl<tiny_tag>
		{
			template <class _tiny, class _pos>
			struct apply : tiny_at<_tiny, _pos::value>
			{
			};
		};

		template <class _tiny, class _pos>
		struct deref<tiny_iterator<_tiny, _pos> > : at<_tiny, _pos>
		{
		};

		template <class _tiny, class _pos, class _index>
		struct advance<tiny_iterator<_tiny, _pos>, _index>
		{
			typedef tiny_iterator<_tiny, typename plus<_pos, _index>::type> type;
		};

		template <class _tiny, class _pos1, class _pos2>
		struct distance<tiny_iterator<_tiny, _pos1>, tiny_iterator<_tiny, _pos2> > : minus<_pos1, _pos2>
		{
		};

		template <>
		struct begin_impl<tiny_tag>
		{
			template <class _tiny>
			struct apply
			{
				typedef tiny_iterator<_tiny, int_<0> > type;
			};
		};

		template <>
		struct end_impl<tiny_tag>
		{
			template <class _tiny>
			struct apply
			{
				typedef tiny_iterator<_tiny, typename tiny_size<typename _tiny::t0, typename _tiny::t1, typename _tiny::t2>::type> type;
			};
		};

		template <>
		struct size_impl<tiny_tag>
		{
			template <class _tiny>
			struct apply : tiny_size<typename _tiny::t0, typename _tiny::t1, typename _tiny::t2>
			{
			};
		};

		template <>
		struct clear_impl<tiny_tag>
		{
			template <class _tiny>
			struct apply : tiny<>
			{
			};
		};

		template <>
		struct push_front_impl<tiny_tag>
		{
			template <class _tiny, class T>
			struct apply : tiny<T, typename _tiny::t0, typename _tiny::t1>
			{
			};
		};

		template <>
		struct push_back_impl<tiny_tag>
		{
			template <class _tiny, class T>
			struct apply : tiny_push_back<_tiny, T, size<_tiny>::value>
			{
			};
		};

	}
}

int main(int argc, char *argv[])
{
	typedef tiny<int, float, long>::type tiny_test;
	BOOST_STATIC_ASSERT((is_same<at<tiny_test, int_<0> >::type, int>::value));
	BOOST_STATIC_ASSERT((is_same<at<tiny_test, int_<1> >::type, float>::value));
	BOOST_STATIC_ASSERT((is_same<at<tiny_test, int_<2> >::type, long>::value));
	typedef begin<tiny_test>::type tt_iter_0;
	BOOST_STATIC_ASSERT((is_same<deref<tt_iter_0>::type, int>::value));
	typedef next<tt_iter_0>::type tt_iter_1;
	BOOST_STATIC_ASSERT((is_same<deref<tt_iter_1>::type, float>::value));
	typedef next<tt_iter_1>::type tt_iter_2;
	BOOST_STATIC_ASSERT((is_same<deref<tt_iter_2>::type, long>::value));
	BOOST_STATIC_ASSERT((is_same<deref<advance<tt_iter_0, int_<2> >::type>::type, deref<tt_iter_2>::type>::value));
	BOOST_STATIC_ASSERT((distance<end<tiny_test>::type, begin<tiny_test>::type>::value == size<tiny_test>::value));
	BOOST_STATIC_ASSERT((is_same<clear<tiny_test>::type, tiny<> >::value));
	BOOST_STATIC_ASSERT((is_same<push_front<tiny<>, int>::type, tiny<int> >::value));
	BOOST_STATIC_ASSERT((is_same<push_front<tiny<int>, float>::type, tiny<float, int> >::value));
	BOOST_STATIC_ASSERT((is_same<push_front<tiny<float, int>, long>::type, tiny<long, float, int> >::value));
	BOOST_STATIC_ASSERT((is_same<push_back<tiny<>, int>::type, tiny<int> >::value));
	BOOST_STATIC_ASSERT((is_same<push_back<tiny<int>, float>::type, tiny<int, float> >::value));
	BOOST_STATIC_ASSERT((is_same<push_back<tiny<float, int>, long>::type, tiny<float, int, long> >::value));
	return 0;
}