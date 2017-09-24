#include "EventCall.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 1280 / 2 - 320;
const int START_POS_Y = 200;
const int CALL_POS_X = 1280 / 2;


EventCall::EventCall( ) :
Event( EVENT_CALL, DIR_LEFT ) {
}


EventCall::~EventCall( ) {
}

void EventCall::update( ) {
	switch ( _phase ) {
	case PHASE_ENTER:
		if ( _player->isEntering( ) ) {
			_player->autoMove( CALL_POS_X );
			_phase = PHASE_MOVE;
		}
		break;
	case PHASE_MOVE:
		if ( _player->isFinishedAutomoving( ) ) {
			_player->call( );
			_phase = PHASE_CALL;
		}
		break;
	case PHASE_CALL:
		if ( _player->isFinishedCalling( ) ) {
			Family::getTask( )->call( _player );
			exit( );
			_phase = PHASE_FINISHED;
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}

void EventCall::join( PLAYER target ) {
	if ( getFade( ) == Event::FADE_OUT ) {
		return;
	}

	//’èˆõˆê–¼
	if ( _player ) {
		return;
	}
	_player = Family::getTask( )->getPlayer( target );
	_player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
}
