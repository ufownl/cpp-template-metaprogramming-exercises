#include <boost/type_traits.hpp>

using namespace boost;

template <class T>
struct add_const_ref
{
	typedef typename T const& type;
};

template <class T>
struct add_const_ref<T&>
{
	typedef typename T& type;
};

int main(int argc, char *argv[])
{
	BOOST_STATIC_ASSERT((is_same<add_const_ref<int>::type, int const&>::value));
	BOOST_STATIC_ASSERT((is_same<add_const_ref<int&>::type, int&>::value));
	BOOST_STATIC_ASSERT((is_same<add_const_ref<int*>::type, int* const&>::value));
	BOOST_STATIC_ASSERT((is_same<add_const_ref<int*&>::type, int*&>::value));
	return 0;
}