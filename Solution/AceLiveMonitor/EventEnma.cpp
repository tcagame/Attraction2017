#include "EventEnma.h"
#include "Family.h"
#include "Player.h"


const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2 - 5;

EventEnma::EventEnma( ) :
Event( EVENT_ENMA, DIR_RIGHT ),
_audience( false ),
_phase( PHASE_ENTER ),
_count( 0 ) {
}


EventEnma::~EventEnma( ) {
}

void EventEnma::update( ) {
	switch ( _phase ) {
	case PHASE_ENTER:
		for ( int i = 0; i < MAX_PLAYER; i++ ) {
			PlayerPtr player = Family::getTask( )->getPlayer( i );
			Player::ACTION action = player->getAction( );
			if ( action != Player::ACTION_ENTERING_FADEOUT &&
			     action != Player::ACTION_ENTERING_SANZO ) {
				_player = player;
			}
		}
		if ( _player ) {
			_player->autoMove( AUDIENCE_POS_X );
			_phase = PHASE_MOVE;
		}
		break;
	case PHASE_MOVE:
		if ( _player->isFinishedAutomoving( ) ) {
			_player->audience( );
			_phase = PHASE_AUDIENCE;
		}
		break;
	case PHASE_AUDIENCE:
		_count++;
		if ( _count > AUDIENCE_COUNT ) {
			_player->setModeVirtue( );
			exit( );
			_phase = PHASE_FINISHED;
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}

bool EventEnma::isJoining( ) const {
	return !_audience;
}

void EventEnma::join( PLAYER target ) {
	//’èˆõˆê–¼
	if ( _audience ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
	start( );
	_audience = true;
}