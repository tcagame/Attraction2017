#include "EventBudha.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2 - 5;

EventBudha::EventBudha( ) :
Event( EVENT_BUDHA, DIR_RIGHT ),
_audience( false ),
_phase( PHASE_ENTER ) {
}


EventBudha::~EventBudha( ) {
}

void EventBudha::update( ) {
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
			exit( );
			_player->setActionEnding( );
			_phase = PHASE_FINISHED;
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}

bool EventBudha::isJoining( ) const {
	return !_audience;
}

void EventBudha::join( PLAYER target ) {
	//’èˆõˆê–¼
	if ( _audience ) {
		return;
	}
	FamilyPtr family( Family::getTask( ) );
	family->getPlayer( target )->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
	start( );
	_audience = true;
}