#include <boost/type_traits.hpp>
#include <stdio.h>

using namespace boost;

template <class F, bool _f_empty, class G, bool _g_empty>
struct storage;

template <class F, class G>
struct storage<F, false, G, false>
{
protected:
	storage(const F &f, const G &g)
		: mf(f)
		, mg(g)
	{
	}

	const F& get_f()
	{
		return mf;
	}

	const G& get_g()
	{
		return mg;
	}

private:
	F mf;
	G mg;
};

template <class F, class G>
struct storage<F, false, G, true> : private G
{
protected:
	storage(const F &f, const G &g)
		: G(g)
		, mf(f)
	{
	}

	const F& get_f()
	{
		return mf;
	}

	const G& get_g()
	{
		return *this;
	}

private:
	F mf;
};

template <class F, class G>
struct storage<F, true, G, false> : private F
{
protected:
	storage(const F &f, const G &g)
		: F(f)
		, mg(g)
	{
	}

	const F& get_f()
	{
		return *this;
	}

	const G& get_g()
	{
		return mg;
	}

private:
	G mg;
};

template <class F, class G>
struct storage<F, true, G, true> : private F, private G
{
protected:
	storage(const F &f, const G &g)
		: F(f)
		, G(g)
	{
	}

	const F& get_f()
	{
		return *this;
	}

	const G& get_g()
	{
		return *this;
	}
};

template <class F>
struct storage<F, true, F, true> : private F
{
protected:
	storage(const F &f, const F &g)
		: F(f)
	{
	}

	const F& get_f()
	{
		return *this;
	}

	const F& get_g()
	{
		return *this;
	}
};

template <class R, class F, class G>
class compose_fg : storage<F, is_empty<F>::value, G, is_empty<G>::value>
{
private:
	typedef storage<F, is_empty<F>::value, G, is_empty<G>::value> base;

public:
	compose_fg(const F &f, const G &g)
		: base(f, g)
	{
	}

	template <class T>
	R operator () (const T &x)
	{
		const F &f = this->get_f();
		const G &g = this->get_g();
		return f(g(x));
	}
};

template <class R, class F, class G>
compose_fg<R, F, G> compose(const F &f, const G &g)
{
	return compose_fg<R, F, G>(f, g);
}

template <class R, class F, F f, class G, G g>
struct compose_fg2
{
	typedef R result_type;

	template <class T>
	R operator () (const T &x)
	{
		return f(g(x));
	}
};

float f_func(int x)
{
	return static_cast<float>(x) / 2;
}

int g_func(int x)
{
	return x + 1;
}

struct f_functor
{
	float operator () (int x) const
	{
		return static_cast<float>(x) / 2;
	}
} f_obj;

struct g_functor
{
	int operator () (int x) const
	{
		return x + 1;
	}
} g_obj;

struct h_functor
{
	float operator () (float x) const
	{
		return x / 2;
	}
} h_obj;

int main(int argc, char *argv[])
{
	float a = compose<float>(&f_func, &g_func)(0);
	float b = compose<float>(&f_func, g_obj)(0);
	float c = compose<float>(f_obj, &g_func)(0);
	float d = compose<float>(f_obj, g_obj)(0);

	printf("%f %f %f %f\n", a, b, c, d);

	size_t as = sizeof(compose<float>(&f_func, &g_func));
	size_t bs = sizeof(compose<float>(&f_func, g_obj));
	size_t cs = sizeof(compose<float>(f_obj, &g_func));
	size_t ds = sizeof(compose<float>(f_obj, g_obj));

	printf("%u %u %u %u\n", as, bs, cs, ds);

	float e = compose<float>(h_obj, h_obj)(8.0f);

	printf("%f\n", e);

	float f = compose_fg2<float, f_functor&, f_obj, g_functor&, g_obj>()(0);

	printf("%f\n", f);

	return 0;
}