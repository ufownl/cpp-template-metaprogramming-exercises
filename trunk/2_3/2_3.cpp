#include <boost/type_traits.hpp>
#include <iostream>
#include <string>
#include <assert.h>

using namespace boost;
using namespace std;

template <class T>
struct type_descriptor;

template <>
struct type_descriptor<char>
{
	operator char const* ()
	{
		return "char";
	}
};

template <>
struct type_descriptor<short int>
{
	operator char const* ()
	{
		return "short int";
	}
};

template <>
struct type_descriptor<int>
{
	operator char const* ()
	{
		return "int";
	}
};

template <>
struct type_descriptor<long int>
{
	operator char const* ()
	{
		return "long int";
	}
};

template <class T>
struct type_descriptor
{
	operator char const* ()
	{
		if (is_const<T>::value)
		{
			ret = type_descriptor<remove_const<T>::type>();
			ret += " const";
		}
		else if (is_pointer<T>::value)
		{
			ret = type_descriptor<remove_pointer<T>::type>();
			ret += "*";
		}
		else if (is_reference<T>::value)
		{
			ret = type_descriptor<remove_reference<T>::type>();
			ret += "&";
		}
		else
		{
			assert(!"Type error.");
		}

		return ret.c_str();
	}

	string ret;
};

int main(int argc, char *argv[])
{
	cout << type_descriptor<int>() << endl;
	cout << type_descriptor<short>() << endl;
	cout << type_descriptor<long>() << endl;
	cout << type_descriptor<const long>() << endl;
	cout << type_descriptor<int*>() << endl;
	cout << type_descriptor<short&>() << endl;
	cout << type_descriptor<long*&>() << endl;
	return 0;
}