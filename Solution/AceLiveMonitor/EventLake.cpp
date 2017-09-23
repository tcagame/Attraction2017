#include "EventLake.h"
#include "Family.h"
#include "Player.h"
#include "NPCMiko.h"
#include "Office.h"

const int START_POS_X = 1280 / 2 + 300;
const int START_POS_Y = 128;
const int AUDIENCE_POS_X = 1280 / 2 - 350;
const int AUDIENCE_COUNT = 100;
const int HEART_COUNT = 30;

EventLake::EventLake( ) :
Event( EVENT_LAKE, DIR_RIGHT ),
_phase(PHASE_ENTER),
_count( 0 ) {
	_npc = std::dynamic_pointer_cast<NPCMiko>( Office::getTask( )->popUpNPC( EVENT_LAKE ) );
}


EventLake::~EventLake( ) {
}

void EventLake::update( ) {
	switch ( _phase ) {
	case PHASE_ENTER:
		if ( _player->isEntering( ) ) {
			_player->autoMove( AUDIENCE_POS_X );
			_phase = PHASE_MOVE;
		}
		break;
	case PHASE_MOVE:
		if ( _player->isFinishedAutomoving( ) ) {
			_player->audience( false );
			_phase = PHASE_AUDIENCE;
		}
		break;
	case PHASE_AUDIENCE:
		_count++;
		if ( _count > AUDIENCE_COUNT ) {
			exit( );
			_phase = PHASE_FINISHED;
		} else {
			if ( _count == HEART_COUNT ) {
				_player->pickUpItem( Player::ITEM_HEART );
			}
			_npc->startSolt( );
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}


void EventLake::join( PLAYER target ) {
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