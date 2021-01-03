#pragma once

class StateMachine
{
public:
	enum State { 
		startup,
		tripod_gait_init,
		tripod_gait,
		default_stand_init,
		default_stand,
		ground_rest_init,
		ground_rest, 
		emergency_stop,
		stop_init,
		stopped, 
	};

	State currentState;
	State goalState;

	StateMachine();
	void setGoalState(State);


private:
	bool setIdle();
	bool set

};

