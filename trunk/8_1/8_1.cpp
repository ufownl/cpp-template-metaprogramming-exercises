#include <stdio.h>
#include <math.h>

#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/assert.hpp>

using namespace boost;
using namespace boost::mpl;

struct nil
{
};

template <class T0 = nil, class T1 = nil, class T2 = nil, class T3 = nil>
struct types
{
};

typedef vector_c<int, 0, 0, 0> Scalar;

typedef vector_c<int, 1, 0, 0> Mass;
typedef vector_c<int, 0, 1, 0> Length;
typedef vector_c<int, 0, 0, 1> Time;

typedef vector_c<int, 0, 1, -1> Velocity;
typedef vector_c<int, 0, 1, -2> Acceleration;
typedef vector_c<int, 1, 1, -1> Momentum;
typedef vector_c<int, 1, 1, -2> Force;

template <class T, class D>
class Quantity
{
public:
	explicit Quantity(const T &val = T(0))
		: mValue(val)
	{
	}

	template <class O>
	Quantity(const Quantity<T, O> &rhs)
		: mValue(rhs.value())
	{
		BOOST_MPL_ASSERT_MSG((equal<D, O>::value), DIMENSIONS_MAST_BE_SAME, (types<D, O>));
	}

	T value() const
	{
		return mValue;
	}

private:
	T mValue;
};

template <class T, class D1, class D2>
Quantity<T, D1> operator + (const Quantity<T, D1> &a, const Quantity<T, D2> &b)
{
	BOOST_MPL_ASSERT_MSG((equal<D1, D2>::value), DIMENSIONS_MAST_BE_SAME, (types<D1, D2>));
	return Quantity<T, D1>(a.value() + b.value());
}

template <class T, class D1, class D2>
Quantity<T, D1> operator - (const Quantity<T, D1> &a, const Quantity<T, D2> &b)
{
	BOOST_MPL_ASSERT_MSG((equal<D1, D2>::value), DIMENSIONS_MAST_BE_SAME, (types<D1, D2>));
	return Quantity<T, D1>(a.value() - b.value());
}

template <class T, class D1, class D2>
Quantity<T, typename transform<D1, D2, plus<_1, _2> >::type> operator * (const Quantity<T, D1> &a, const Quantity<T, D2> &b)
{
	return Quantity<T, typename transform<D1, D2, plus<_1, _2> >::type>(a.value() * b.value());
}

template <class T, class D1, class D2>
Quantity<T, typename transform<D1, D2, minus<_1, _2> >::type> operator / (const Quantity<T, D1> &a, const Quantity<T, D2> &b)
{
	return Quantity<T, typename transform<D1, D2, minus<_1, _2> >::type>(a.value() / b.value());
}

int main(int argc, char *argv[])
{
	Quantity<float, Mass> m(2.5f);
	Quantity<float, Acceleration> a(10.0f);
	Quantity<float, Force> f = m * a;
	
	f = f + m * a;
	printf("%f\n", f.value());

	return 0;
}