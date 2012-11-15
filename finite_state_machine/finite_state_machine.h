#ifndef __FSM_finite_state_machine_H__
#define __FSM_finite_state_machine_H__

#include "generate_dispatcher.h"

#include <assert.h>

template <class T>
class finite_state_machine
{
public:
	template <class _event>
	int process_event(const _event &e)
	{
		typedef typename generate_dispatcher<T::transition_table, _event>::type dispatcher;

		m_state = dispatcher::dispatch(*static_cast<T*>(this), m_state, e);
		return m_state;
	}

	int current_state() const
	{
		return m_state;
	}

protected:
	finite_state_machine()
		: m_state(T::initial_state)
	{
	}

	template <int _current_state, class _event, int _next_state, void (T::*_action)(const _event&)>
	struct row
	{
		static const int current_state = _current_state;
		static const int next_state = _next_state;
		typedef _event event;
		typedef T fsm_t;

		static void execute(T &fsm, const _event &e)
		{
			(fsm.*_action)(e);
		}
	};

	template <class _event>
	int call_no_transition(int state, const _event &e)
	{
		return static_cast<T*>(this)->no_transition(state, e);
	}

	template <class _event>
	int no_transition(int state, const _event &e)
	{
		assert(!"no transition.");
		return state;
	}

private:
	friend struct default_event_dispatch;

private:
	int m_state;
};

#include "event_dispatcher.h"

#endif  // __FSM_finite_state_machine_H__