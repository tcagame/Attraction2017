#include "EventRyugu.h"
#include "Office.h"
#include "Family.h"
#include "Player.h"
#include "Storage.h"
#include "ItemBox.h"

const int START_POS_X = 256 + 128;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2 - 100;
const int FINISHED_COUNT = 60;

EventRyugu::EventRyugu( ) :
Event( EVENT_RYUGU, DIR_LEFT ),
_count( 0 ),
_phase( PHASE_ENTER ) {
	Office::getTask( )->popUpNPC( EVENT_RYUGU );
	//‹ÊŽè” ‚ð‰æ–Ê’†‰›‚ÉB1
	StoragePtr storage = Storage::getTask( );
	ItemPtr box = ItemPtr( new ItemBox( ) );
	_box = box;
	storage->add( box );
}


EventRyugu::~EventRyugu( ) {
}

void EventRyugu::update( ) {
	switch ( _phase ) {
	case PHASE_ENTER:
		if ( _player->isEntering( ) ) {
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
			_player->free( );
			_phase = PHASE_FREE;
		}
		break;
	case PHASE_FREE:
		if ( !_box.lock( ) ) {
			_count = 0;
			_phase= PHASE_FINISHED;
		}
		escape( );
		break;
	case PHASE_FINISHED:
		_count++;
		if ( _count > FINISHED_COUNT ) {
			exit( );
		}
		break;
	}
}

void EventRyugu::join( PLAYER target ) {
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