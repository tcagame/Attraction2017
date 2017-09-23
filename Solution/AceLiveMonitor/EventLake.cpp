#include "EventLake.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 1280 / 2;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2 - 5;

EventLake::EventLake( ) :
Event( EVENT_LAKE, DIR_RIGHT ),
_phase(PHASE_ENTER),
_count(0) {
}


EventLake::~EventLake( ) {
}

void EventLake::update( ) {
	switch (_phase) {
	case PHASE_ENTER:
		if (_player->isEntering()) {
			_player->autoMove(AUDIENCE_POS_X);
			_phase = PHASE_MOVE;
		}
		break;
	case PHASE_MOVE:
		/*if (_player->isFinishedAutomoving()) {
			_player->audience();
			_phase = PHASE_AUDIENCE;
		}*/
		break;
	case PHASE_AUDIENCE:
		_count++;
		if (_count > AUDIENCE_COUNT) {
			_player->setModeVirtue();
			exit();
			_phase = PHASE_FINISHED;
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}


void EventLake::join( PLAYER target ) {
	if (getFade() == Event::FADE_OUT) {
		return;
	}

	//’èˆõˆê–¼
	if (_player) {
		return;
	}
	_player = Family::getTask()->getPlayer(target);
	_player->enterEvent(Vector(START_POS_X, START_POS_Y), Player::ENTER_FADEOUT);
	start();
}