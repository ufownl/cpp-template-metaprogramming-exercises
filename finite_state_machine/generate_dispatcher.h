#ifndef __FSM_generate_dispatcher_H__
#define __FSM_generate_dispatcher_H__

#include <boost/type_traits.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/filter_view.hpp>

template <class _row, class _next>
struct event_dispatcher;

struct default_event_dispatch;

template <class _row>
struct transition_event
{
	typedef typename _row::event type;
};

template <class _table, class _event>
struct generate_dispatcher
	: boost::mpl::fold<
		boost::mpl::filter_view<
			_table,
			boost::is_same<
				_event,
				transition_event<boost::mpl::_1>
			>
		>,
		default_event_dispatch,
		event_dispatcher<boost::mpl::_2, boost::mpl::_1>
	>
{
};

#endif  // __FSM_generate_dispatcher_H__