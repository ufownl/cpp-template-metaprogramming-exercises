#include <boost/type_traits.hpp>

using namespace boost;

template <class C, class T1, class T2>
struct replace_type;

template <class C, class T1, class T2, bool _same>
struct replace_type_impl
{
	typedef C type;
};

template <class C, class T1, class T2>
struct replace_type_impl<C, T1, T2, true>
{
	typedef T2 type;
};

template <class C, class T1, class T2>
struct replace_type_impl<C const, T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type const type;
};

template <class C, class T1, class T2>
struct replace_type_impl<C*, T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type* type;
};

template <class C, class T1, class T2>
struct replace_type_impl<C&, T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type& type;
};

template <class C, class T1, class T2>
struct replace_type_impl<C[], T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type type[];
};

template <class C, class T1, class T2, size_t N>
struct replace_type_impl<C[N], T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type type[N];
};

template <class C, class T1, class T2>
struct replace_type_impl<C(), T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type type();
};

template <class C, class T1, class T2, class A1>
struct replace_type_impl<C(A1), T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type type(typename replace_type<A1, T1, T2>::type);
};

template <class C, class T1, class T2, class A1, class A2>
struct replace_type_impl<C(A1, A2), T1, T2, false>
{
	typedef typename replace_type<C, T1, T2>::type type(typename replace_type<A1, T1, T2>::type, typename replace_type<A2, T1, T2>::type);
};

template <class C, class T1, class T2>
struct replace_type
{
	typedef typename replace_type_impl<C, T1, T2, is_same<C, T1>::value>::type type;
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((is_same<replace_type<int, int, float>::type, float>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int*, int, float>::type, float*>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int const, int, float>::type, float const>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int* const, int, float>::type, float* const>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int const*, int, float>::type, float const*>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int const*, int const, float>::type, float*>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int* const, int*, float>::type, float const>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int, long, float>::type, int>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int(), int, float>::type, float()>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int(int[]), int, float>::type, float(float[])>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int(int*, int const&), int, float>::type, float(float*, float const&)>::value));
	BOOST_STATIC_ASSERT((is_same<replace_type<int(int*, double const&), int, float>::type, float(float*, double const&)>::value));
	return 0;
}
