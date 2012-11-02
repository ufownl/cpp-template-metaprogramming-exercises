#include <iostream>
#include <string>

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
struct type_descriptor<T const>
{
	operator char const* ()
	{
		ret = type_descriptor<T>();
		ret += " const";
		return ret.c_str();
	}

	string ret;
};

template <class T>
struct type_descriptor<T*>
{
	operator char const* ()
	{
		ret = type_descriptor<T>();
		ret += "*";
		return ret.c_str();
	}

	string ret;
};

template <class T>
struct type_descriptor<T&>
{
	operator char const* ()
	{
		ret = type_descriptor<T>();
		ret += "&";
		return ret.c_str();
	}

	string ret;
};

template <class T>
struct type_descriptor<T[]>
{
	operator char const* ()
	{
		ret = type_descriptor<T>();
		ret += "[]";
		return ret.c_str();
	}

	string ret;
};

template <class T, size_t N>
struct type_descriptor<T[N]>
{
	operator char const* ()
	{
		char buf[16];

		sprintf(buf, "%u", N);

		ret = type_descriptor<T>();
		ret += "[";
		ret += buf;
		ret += "]";
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
	cout << type_descriptor<int[]>() << endl;
	cout << type_descriptor<int[5]>() << endl;
	return 0;
}