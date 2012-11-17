#ifndef __FSM_generate_dispatcher_H__
#define __FSM_generate_dispatcher_H__

#include <boost/type_traits.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/copy.hpp>
#include <boost/mpl/back_inserter.hpp>
#include <boost/mpl/sort.hpp>
#include <boost/mpl/advance.hpp>
#include <boost/mpl/distance.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/divides.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/filter_view.hpp>

template <class _row, class _left, class _right>
struct event_dispatcher;

struct default_event_dispatch;

template <class _it0, class _it1>
struct generate_dispatcher_impl
{
	typedef typename boost::mpl::advance<
		_it0,
		typename boost::mpl::divides<
			typename boost::mpl::distance<_it0, _it1>::type,
			boost::mpl::int_<2>
		>::type
	>::type middle;
	typedef event_dispatcher<
		typename boost::mpl::deref<middle>::type,
		generate_dispatcher_impl<_it0, middle>,
		generate_dispatcher_impl<typename boost::mpl::next<middle>::type, _it1>
	> type;
};

template <class _it>
struct generate_dispatcher_impl<_it, _it>
{
	typedef default_event_dispatch type;
};

template <class _row>
struct transition_event
{
	typedef typename _row::event type;
};

template <class _row0, class _row1>
struct transition_less
	: boost::mpl::less<
		boost::mpl::int_<_row0::current_state>,
		boost::mpl::int_<_row1::current_state>
	>
{
};

template <class _table, class _event>
struct generate_dispatcher
{
	typedef typename boost::mpl::copy<
		boost::mpl::filter_view<
			typename boost::mpl::sort<
				_table,
				transition_less<boost::mpl::_1, boost::mpl::_2>
			>::type,
			boost::is_same<
				_event,
				transition_event<boost::mpl::_1>
			>
		>,
		boost::mpl::back_inserter<typename boost::mpl::clear<_table>::type>
	>::type seq;
	typedef typename generate_dispatcher_impl<
		typename boost::mpl::begin<seq>::type,
		typename boost::mpl::end<seq>::type
	>::type type;
};

#endif  // __FSM_generate_dispatcher_H__