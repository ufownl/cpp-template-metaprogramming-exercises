#ifndef __FSM_event_dispatcher_H__
#define __FSM_event_dispatcher_H__

template <class _row, class _left, class _right>
struct event_dispatcher
{
	typedef typename _row::fsm_t fsm_t;
	typedef typename _row::event event;
	typedef event_dispatcher type;

	static int dispatch(fsm_t &fsm, int state, const event &e)
	{
		if (state == _row::current_state)
		{
			_row::execute(fsm, e);
			return _row::next_state;
		}
		else if (state < _row::current_state)
		{
			return _left::type::dispatch(fsm, state, e);
		}
		else
		{
			return _right::type::dispatch(fsm, state, e);
		}
	}
};

struct default_event_dispatch
{
	typedef default_event_dispatch type;

	template <class _fsm, class _event>
	static int dispatch(finite_state_machine<_fsm> &fsm, int state, const _event &e)
	{
		return fsm.call_no_transition(state, e);
	}
};

#endif  // __FSM_event_dispatcher_H__