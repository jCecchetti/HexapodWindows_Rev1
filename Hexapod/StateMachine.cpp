#include "StateMachine.h"

StateMachine::StateMachine() {
	currentState = startup;
	goalState = default_stand;
}

void StateMachine::setGoalState(State goalState) {
	this->goalState = goalState;
}