#include <boost/type_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
//#include <boost/mpl/bool.hpp>

using namespace boost;
using namespace boost::mpl;

template <class T>
struct is_data_member_pointer : is_member_object_pointer<T>
{
};

template <class T>
struct is_pointer_to_function : and_<is_pointer<T>, is_function<typename remove_pointer<T>::type> >
{
};

template <class T>
struct is_reference_to_function_pointer : and_<is_reference<T>, is_pointer_to_function<typename remove_reference<T>::type> >
{
};

template <class T>
struct is_reference_to_non_const : and_<is_reference<T>, not_<is_const<typename remove_reference<T>::type> > >
{
};

struct test
{
	void func() {}
	int data;
};

void test_func() {}
int test_data;

template <class T1, class T2>
void test_is_data_member_pointer(T1, T2)
{
	BOOST_STATIC_ASSERT((is_data_member_pointer<T1>::value));
	BOOST_STATIC_ASSERT((!is_data_member_pointer<T2>::value));
}

template <class T1, class T2>
void test_is_pointer_to_function(T1, T2)
{
	BOOST_STATIC_ASSERT((is_pointer_to_function<T1>::value));
	BOOST_STATIC_ASSERT((!is_pointer_to_function<T2>::value));
}

template <class T1, class T2>
void test_is_reference_to_function_pointer(T1, T2)
{
	BOOST_STATIC_ASSERT((is_reference_to_function_pointer<typename add_reference<T1>::type>::value));
	BOOST_STATIC_ASSERT((!is_reference_to_function_pointer<typename add_reference<T2>::type>::value));
}

template <class T1>
void test_is_reference_to_non_const(T1)
{
	BOOST_STATIC_ASSERT((is_reference_to_non_const<typename add_reference<T1>::type>::value));
	BOOST_STATIC_ASSERT((!is_reference_to_non_const<typename add_reference<typename add_const<T1>::type>::type>::value));
}

int main(int argc, char *argv[])
{
	test_is_data_member_pointer(&test::data, &test::func);
	test_is_pointer_to_function(&test_func, &test_data);
	test_is_reference_to_function_pointer(&test_func, &test_data);
	test_is_reference_to_non_const(test_data);
	return 0;
}