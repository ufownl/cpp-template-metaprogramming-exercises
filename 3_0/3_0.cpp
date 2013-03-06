#include <stdio.h>
#include <boost/static_assert.hpp>

template <size_t N>
struct binary
{
	BOOST_STATIC_ASSERT(N % 10 < 2);
	static size_t const value = binary<N / 10>::value * 2 + N % 10;
};

template <>
struct binary<0>
{
	static size_t const value = 0;
};

int main(int argc, char *argv[])
{
	printf("%lu\n", binary<101>::value);
	return 0;
}
