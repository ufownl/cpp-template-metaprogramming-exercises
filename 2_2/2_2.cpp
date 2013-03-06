#include <boost/type_traits.hpp>
#include <assert.h>

using namespace boost;

template <class Target, class Source>
Target polymorphic_downcast(Source *ptr)
{
	assert(dynamic_cast<Target>(ptr) == ptr);
	return static_cast<Target>(ptr);
}

template <class Target, class Source>
Target polymorphic_downcast(Source &ref)
{
	assert(dynamic_cast<typename add_pointer<typename remove_reference<Target>::type>::type>(&ref) == &ref);
	return static_cast<Target>(ref);
}

struct A { virtual ~A() {} };
struct B : A {};

int main(int argc, char *argv[])
{
	B b;

	A *a_ptr = &b;
	B *b_ptr = polymorphic_downcast<B*>(a_ptr);

	A &a_ref = b;
	B &b_ref = polymorphic_downcast<B&>(a_ref);

	return 0;
}
