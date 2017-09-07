#include "RockMapStreet.h"
#include "RockFamily.h"
#include "RockPlayer.h"
#include "RockMapStreetDrawer.h"
#include "Status.h"
#include "MessageSender.h"
#include "RockStorage.h"
#include "RockItemToku.h"
#include "RockItemMoney.h"
#include "RockOffice.h"
#include "EventTurtle.h"

const int REMOVE_CAVE_TIME = 500;
const int DROP_TIMING = 1800;

RockMapStreet::RockMapStreet( StatusPtr status ) :
_time( 0 ),
_virtue_pop( false ),
_status( status ) {
}

RockMapStreet::~RockMapStreet( ) {
}

void RockMapStreet::initialize( ) {
	_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( STAGE_STREET ) );

	{//street初期化
		_stage = STAGE_STREET;
		RockStoragePtr storage = RockStorage::getTask( );
		int interval = 200;
		for ( int i = 0; i < 30; i++ ) {
			storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * interval, 200, -500 - i * 10 ), 10000 ) ) );
		}
		RockOffice::getTask( )->add( RockEventCharacterPtr( new EventTurtle( Vector( 3610, 350, -210 ) ) ) );
	}

}

void RockMapStreet::update( ) {
	switch ( _stage ) {
	case STAGE_STREET:
		updateStreet( );
		break;
	case STAGE_CAVE:
		updateCave( );
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
				_stage = STAGE_CAVE;
				_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( _stage ) );
				family->resetPos( Vector( 0, 10, 0 ) );
			}
		}

		//STREET3のプレイヤーがいれば徳アイテムをポップ
		if ( !_virtue_pop ) {
			Status::Player status = _status->getPlayer( i );
			if ( status.area == AREA_STREET_3 ) {
				_virtue_pop = true;
				RockStoragePtr storage = RockStorage::getTask( );
				for ( int j = 0; j < 30; j++ ) {
					int interval = 200;
					storage->addItem( RockItemPtr( new RockItemToku( Vector( j * interval + interval / 2, 500, -500 - j * 10 ) ) ) );
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
			_stage = STAGE_STREET;
			_drawer = RockMapStreetDrawerPtr( new RockMapStreetDrawer( _stage ) );
			family->resetPos( Vector( 0, 30, -500 ) );
			_time = 0;
			int interval = 80;
			RockStoragePtr storage = RockStorage::getTask( );
			for ( int i = 0; i < 50; i++ ) {
				storage->addItem( RockItemPtr( new RockItemMoney( Vector( i * interval, 500, -500 - i * 10 ), 10000 ) ) );
			}
		}
	}
}
