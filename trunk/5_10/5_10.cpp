#include <boost/type_traits.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/equal.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _root, class _left_child, class _right_child>
struct tree
{
};

struct nil
{
};

template <class _tree>
struct root
{
	typedef _tree type;
};

template <class _root, class _left_child, class _right_child>
struct root<tree<_root, _left_child, _right_child> >
{
	typedef _root type;
};

template <class _tree>
struct left_child
{
	typedef nil type;
};

template <class _root, class _left_child, class _right_child>
struct left_child<tree<_root, _left_child, _right_child> >
{
	typedef _left_child type;
};

template <class _tree>
struct right_child
{
	typedef nil type;
};

template <class _root, class _left_child, class _right_child>
struct right_child<tree<_root, _left_child, _right_child> >
{
	typedef _right_child type;
};

template <class _seq, class _root, class _left_child, class _right_child>
struct preorder_view_impl
	: preorder_view_impl<
		typename preorder_view_impl<
			typename preorder_view_impl<
				_seq,
				typename root<_root>::type,
				typename left_child<_root>::type,
				typename right_child<_root>::type
			>::type,
			typename root<_left_child>::type,
			typename left_child<_left_child>::type,
			typename right_child<_left_child>::type
		>::type,
		typename root<_right_child>::type,
		typename left_child<_right_child>::type,
		typename right_child<_right_child>::type
	>
{
};

template <class _seq, class _root>
struct preorder_view_impl<_seq, _root, nil, nil> : push_back<_seq, _root>
{
};

template <class _seq>
struct preorder_view_impl<_seq, nil, nil, nil> : _seq
{
};

template <class _tree>
struct preorder_view
	: preorder_view_impl<
		vector<>,
		typename root<_tree>::type,
		typename left_child<_tree>::type,
		typename right_child<_tree>::type
	>
{
};

template <class _seq, class _root, class _left_child, class _right_child>
struct inorder_view_impl
	: inorder_view_impl<
		typename inorder_view_impl<
			typename inorder_view_impl<
				_seq,
				typename root<_left_child>::type,
				typename left_child<_left_child>::type,
				typename right_child<_left_child>::type
			>::type,
			typename root<_root>::type,
			typename left_child<_root>::type,
			typename right_child<_root>::type
		>::type,
		typename root<_right_child>::type,
		typename left_child<_right_child>::type,
		typename right_child<_right_child>::type
	>
{
};

template <class _seq, class _root>
struct inorder_view_impl<_seq, _root, nil, nil> : push_back<_seq, _root>
{
};

template <class _seq>
struct inorder_view_impl<_seq, nil, nil, nil> : _seq
{
};

template <class _tree>
struct inorder_view
	: inorder_view_impl<
		vector<>,
		typename root<_tree>::type,
		typename left_child<_tree>::type,
		typename right_child<_tree>::type
	>
{
};

template <class _seq, class _root, class _left_child, class _right_child>
struct postorder_view_impl
	: postorder_view_impl<
		typename postorder_view_impl<
			typename postorder_view_impl<
				_seq,
				typename root<_left_child>::type,
				typename left_child<_left_child>::type,
				typename right_child<_left_child>::type
			>::type,
			typename root<_right_child>::type,
			typename left_child<_right_child>::type,
			typename right_child<_right_child>::type
		>::type,
		typename root<_root>::type,
		typename left_child<_root>::type,
		typename right_child<_root>::type
	>
{
};

template <class _seq, class _root>
struct postorder_view_impl<_seq, _root, nil, nil> : push_back<_seq, _root>
{
};

template <class _seq>
struct postorder_view_impl<_seq, nil, nil, nil> : _seq
{
};

template <class _tree>
struct postorder_view
	: postorder_view_impl<
		vector<>,
		typename root<_tree>::type,
		typename left_child<_tree>::type,
		typename right_child<_tree>::type
	>
{
};

int main(int argc, char *argv[])
{
	typedef tree<double, tree<void*, int, long>, char> tree_seq_0;
	BOOST_STATIC_ASSERT((equal<preorder_view<tree_seq_0>::type, vector<double, void*, int, long, char> >::value));
	BOOST_STATIC_ASSERT((equal<inorder_view<tree_seq_0>::type, vector<int, void*, long, double, char> >::value));
	BOOST_STATIC_ASSERT((equal<postorder_view<tree_seq_0>::type, vector<int, long, void*, char, double> >::value));
	typedef tree<double, tree<void*, int, nil>, char> tree_seq_1;
	BOOST_STATIC_ASSERT((equal<preorder_view<tree_seq_1>::type, vector<double, void*, int, char> >::value));
	BOOST_STATIC_ASSERT((equal<inorder_view<tree_seq_1>::type, vector<int, void*, double, char> >::value));
	BOOST_STATIC_ASSERT((equal<postorder_view<tree_seq_1>::type, vector<int, void*, char, double> >::value));
	typedef tree<double, tree<void*, nil, long>, char> tree_seq_2;
	BOOST_STATIC_ASSERT((equal<preorder_view<tree_seq_2>::type, vector<double, void*, long, char> >::value));
	BOOST_STATIC_ASSERT((equal<inorder_view<tree_seq_2>::type, vector<void*, long, double, char> >::value));
	BOOST_STATIC_ASSERT((equal<postorder_view<tree_seq_2>::type, vector<long, void*, char, double> >::value));
	return 0;
}