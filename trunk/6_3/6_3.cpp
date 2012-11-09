#include <boost/type_traits.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/push_back.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/equal.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/inserter.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/mpl/identity.hpp>

using namespace boost;
using namespace boost::mpl;

template <class _root, class _left_child, class _right_child>
struct tree
{
};

struct none
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
	typedef none type;
};

template <class _root, class _left_child, class _right_child>
struct left_child<tree<_root, _left_child, _right_child> >
{
	typedef _left_child type;
};

template <class _tree>
struct right_child
{
	typedef none type;
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
struct preorder_view_impl<_seq, _root, none, none> : push_back<_seq, _root>
{
};

template <class _seq>
struct preorder_view_impl<_seq, none, none, none> : _seq
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
struct inorder_view_impl<_seq, _root, none, none> : push_back<_seq, _root>
{
};

template <class _seq>
struct inorder_view_impl<_seq, none, none, none> : _seq
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
struct postorder_view_impl<_seq, _root, none, none> : push_back<_seq, _root>
{
};

template <class _seq>
struct postorder_view_impl<_seq, none, none, none> : _seq
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

template <class _tree, class T>
struct binary_tree_insert
	: eval_if<
		less<T, typename root<_tree>::type>,
		identity<
			tree<
				typename root<_tree>::type,
				typename binary_tree_insert<typename left_child<_tree>::type, T>::type,
				typename right_child<_tree>::type
			>
		>,
		identity<
			tree<
				typename root<_tree>::type,
				typename left_child<_tree>::type,
				typename binary_tree_insert<typename right_child<_tree>::type, T>::type
			>
		>
	>
{
};

template <class T>
struct binary_tree_insert<none, T> : T
{
};

template <class _tree>
struct binary_tree_inserter : inserter<_tree, binary_tree_insert<_1, _2> >
{
};

int main(int argc, char *argv[])
{
	typedef mpl::copy<vector_c<int, 17, 25, 10, 2, 11>, binary_tree_inserter<none> >::type bst;
	BOOST_STATIC_ASSERT((equal<inorder_view<bst>::type, vector_c<int, 2, 10, 11, 17, 25> >::value));
	return 0;
}