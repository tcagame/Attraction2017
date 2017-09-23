#include "EventReddaemon.h"
#include "Military.h"
#include "EnemyBossRedDaemon.h"
#include "Family.h"
#include "Player.h"
#include "Storage.h"
#include "ItemMoney.h"

const int START_POS_X = 256 + ( 1280 / 2 - 256 ) / 2;
const int START_POS_Y = 128;
const int FINISHED_COUNT = 150;

EventReddaemon::EventReddaemon( ) :
Event( EVENT_REDDAEMON, DIR_LEFT ),
_phase( PHASE_NORMAL ) {
	_boss = EnemyBossPtr( new EnemyBossRedDaemon( Vector( 900, 220 ) ) );
	Military::getTask( )->popUp( _boss );
	_count = 0;
}


EventReddaemon::~EventReddaemon( ) {
}

void EventReddaemon::update( ) {
	// ƒ{ƒX‚ð“|‚µ‚½
	switch ( _phase ) {
	case PHASE_NORMAL:
		if ( _boss->getPower( ) <= 0 ) {
			_phase = PHASE_FINISHED;
		}
		escape( );
		break;
	case PHASE_FINISHED:
		{
			ItemPtr item = ItemPtr( new ItemMoney( Vector( rand( ) % 640 + 320, 20 ), OBJECT_MONEY_PURSE, AREA_EVENT ) );
			item->setDrop( );
			Storage::getTask( )->add( item );

			_count++;
			if ( _count > FINISHED_COUNT ) {
				exit( );
				_phase = PHASE_WAIT;
			}
			break;
		}
	case PHASE_WAIT:
		break;
	}
}

void EventReddaemon::join( PLAYER target ) {
	if ( getFade( ) == FADE_OUT ) {
		return;
	}
	PlayerPtr player = Family::getTask( )->getPlayer( target );
	player->enterEvent( Vector( START_POS_X, START_POS_Y ), Player::ENTER_FADEOUT );
}