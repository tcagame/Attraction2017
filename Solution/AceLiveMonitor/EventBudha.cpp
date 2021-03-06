#include "EventBudha.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"

const int START_POS_X = 256 + 128;
const int START_POS_Y = 128;
const int AUDIENCE_COUNT = 100;
const int AUDIENCE_POS_X = 1280 / 2 - 5;

EventBudha::EventBudha( ) :
Event( EVENT_BUDHA, DIR_RIGHT ),
_phase( PHASE_ENTER ) {
}


EventBudha::~EventBudha( ) {
}

void EventBudha::update( ) {
	switch ( _phase ) {
	case PHASE_ENTER:
		_player->autoMove( AUDIENCE_POS_X );
		_phase = PHASE_MOVE;
		break;
	case PHASE_MOVE:
		if ( _player->isFinishedAutomoving( ) ) {
			_player->audience( );
			SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_BUDHA );
			_phase = PHASE_AUDIENCE;
		}
		break;
	case PHASE_AUDIENCE:
		_count++;
		if ( _count > AUDIENCE_COUNT ) {
			SynchronousData::getTask( )->setStatusMessage( _player->getPlayer( ), SynchronousData::MES_NONE );
			exit( );
			_player->setActionEnding( );
			_phase = PHASE_FINISHED;
		}
		break;
	case PHASE_FINISHED:
		break;
	}
}

void EventBudha::join( PLAYER target ) {
	if ( getFade( ) == Event::FADE_OUT ) {
		return;
	}

	//����ꖼ
	if ( _player ) {
		return;
	}
	_player = Family::getTask( )->getPlayer( target );
	_player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_SANZO );
}