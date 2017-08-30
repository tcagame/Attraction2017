#include "RockMapStreet.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMapStreetDrawer.h"
#include "Status.h"
#include "MessageSender.h"
#include "RockStorage.h"
#include "RockItemToku.h"
#include "RockItemMoney.h"

const int REMOVE_CAVE_TIME = 300;

RockMapStreet::RockMapStreet( StatusPtr status ) :
_time( 0 ),
_status( status ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );

	{//street初期化
		_state = STATE_STREET;
		RockStoragePtr storage = RockStorage::getTask( );
		int interval = 80;
		for ( int i = 0; i < 50; i++ ) {
			storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * interval, 200, -500 - i * 5 ), 10000 ) ) );
		}
	}

}

void RockMapStreet::update( ) {
	switch ( _state ) {
	case STATE_STREET:
		updateStreet( );
		break;
	case STATE_CAVE:
		updateCave( );
		break;
	case STATE_TOKU:
		updateToku( );
		break;
	}
}

void RockMapStreet::updateStreet( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		{//鳥居へ行くとSTAGE_CAVEへ移動
			double length = ( Vector( -200, 0, -500 ) - player->getPos( ) ).getLength( );
			if ( length < 100 ) {
				_drawer.reset( );
				_state = STATE_CAVE;
				_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_CAVE ) );
				family->resetPos( Vector( 0, 10, 0 ) );
			}
		}

		{//一定以上のお金を集めると、STAGE_TOKUへ移動
			Status::Player status = _status->getPlayer( i );
			if ( status.money >= TRANSITION_MONEY_NUM ) {
				_state = STATE_TOKU;
				RockStoragePtr storage = RockStorage::getTask( );
				for ( int i = 0; i < 50; i++ ) {
					int interval = 80;
					storage->addItem( RockItemPtr( new RockItemToku( Vector( i * interval + interval / 2, 200, -500 - i * 5 ) ) ) );
				}
			}
		}
	}
}

void RockMapStreet::updateCave( ) {
	_time++;
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}

		if ( _time > REMOVE_CAVE_TIME ) {
			_drawer.reset( );
			_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );
			family->resetPos( Vector( 0, 30, -500 ) );
			_time = 0;
		}
	}
}

void RockMapStreet::updateToku( ) {
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ) {
			continue;
		}
		{//一定以上の徳を集めると、リザルトマップへ
			Status::Player status = _status->getPlayer( i );
			if ( status.toku >= TRANSITION_TOKU_NUM ) {
				unsigned int state = STATE_RESULT;
				MessageSender::getTask( )->sendMessage( i, Message::COMMAND_STATE, &state );
			}
		}
	}
}