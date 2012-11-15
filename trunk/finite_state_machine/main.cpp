#include "finite_state_machine.h"

#include <boost/mpl/vector.hpp>
#include <stdio.h>

class player : public finite_state_machine<player>
{
public:
	struct play {};
	struct pause {};
	struct stop {};
	struct open_close {};
	
private:
	void open_player(const open_close&)
	{
		puts(__FUNCTION__);
	}

	void close_player(const open_close&)
	{
		puts(__FUNCTION__);
	}

	void start_play(const play&)
	{
		puts(__FUNCTION__);
	}

	void resume_play(const play&)
	{
		puts(__FUNCTION__);
	}

	void pause_play(const pause&)
	{
		puts(__FUNCTION__);
	}

	void stop_play(const stop&)
	{
		puts(__FUNCTION__);
	}

	enum
	{
		close_state,
		stop_state,
		pause_state,
		playing_state,
		initial_state = close_state
	};

	friend class finite_state_machine<player>;

	struct transition_table
		: boost::mpl::vector<
			//    开始状态        事件            下一状态        动作
			//  +---------------+---------------+---------------+-----------------------+
			row < close_state	, open_close	, stop_state	, &player::open_player	>,
			//  +---------------+---------------+---------------+-----------------------+
			row < stop_state	, open_close	, close_state	, &player::close_player	>,
			row < stop_state	, play			, playing_state	, &player::start_play	>,
			//  +---------------+---------------+---------------+-----------------------+
			row < playing_state	, open_close	, close_state	, &player::close_player >,
			row < playing_state	, stop			, stop_state	, &player::stop_play	>,
			row < playing_state	, pause			, pause_state	, &player::pause_play	>,
			//  +---------------+---------------+---------------+-----------------------+
			row < pause_state	, open_close	, close_state	, &player::close_player >,
			row < pause_state	, stop			, stop_state	, &player::stop_play	>,
			row < pause_state	, play			, playing_state	, &player::resume_play	>
			//  +---------------+---------------+---------------+-----------------------+
		>
	{
	};
};

int main(int argc, char *argv[])
{
	player p;

	p.process_event(player::open_close());
	p.process_event(player::play());
	p.process_event(player::pause());
	p.process_event(player::play());
	p.process_event(player::stop());
	p.process_event(player::open_close());

	return 0;
}