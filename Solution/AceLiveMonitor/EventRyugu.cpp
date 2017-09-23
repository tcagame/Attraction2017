#include "EventRyugu.h"
#include "Office.h"
#include "Family.h"
#include "Player.h"

const int START_POS_X = 1280 / 2 - 100;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2;

EventRyugu::EventRyugu( ) :
Event( EVENT_RYUGU, DIR_RIGHT ),
_audience( false ),
_count( 0 ),
_phase( PHASE_ENTER ) {
	Office::getTask( )->popUpNPC( EVENT_RYUGU );
	//‹Êè” ‚ğ‰æ–Ê’†‰›‚ÉB1
}


EventRyugu::~EventRyugu( ) {
}

void EventRyugu::update( ) {
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

bool EventRyugu::isJoining( ) const {
	return !_audience;
}

void EventRyugu::join( PLAYER target ) {
	//’èˆõˆê–¼
	if ( _audience ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
	start( );
	_audience = true;
}