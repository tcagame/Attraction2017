#include "World.h"
#include "Map.h"
#include "SynchronousData.h"
#include "Application.h"
#include "Sound.h"
#include "Family.h"
#include "Player.h"
#include "Military.h"
#include "Office.h"
#include "Storage.h"
#include "Armoury.h"
#include "ItemVirtue.h"
#include "Keyboard.h"

#include "EventTitle.h"
#include "EventReddaemon.h"
#include "EventFlame.h"
#include "EventWood.h"
#include "EventMineral.h"
#include "EventShop.h"
#include "EventRyugu.h"
#include "EventLake.h"
#include "EventCall.h"
#include "EventGamble.h"
#include "EventEnma.h"
#include "EventBudha.h"


const int VIRTUE_RANGE = 1300;

const char * FILENAME_STREET          = "Resource/Ace/Street/mapdata";
const char * FILENAME_EVENT_REDDAEMON = "Resource/Ace/Event/Reddaemon/mapdata";
const char * FILENAME_EVENT_FIRE      = "Resource/Ace/Event/Fire/mapdata";
const char * FILENAME_EVENT_TREE      = "Resource/Ace/Event/Tree/mapdata";
const char * FILENAME_EVENT_ROCK      = "Resource/Ace/Event/Rock/mapdata";
const char * FILENAME_EVENT_SHOP      = "Resource/Ace/Event/Shop/mapdata";
const char * FILENAME_EVENT_RYUGU     = "Resource/Ace/Event/Ryugu/mapdata"; 
const char * FILENAME_EVENT_LAKE      = "Resource/Ace/Event/Lake/mapdata";
const char * FILENAME_EVENT_CALL 	  = "Resource/Ace/Event/Call/mapdata";
const char * FILENAME_EVENT_GAMBLE	  = "Resource/Ace/Event/Gamble/mapdata";
const char * FILENAME_EVENT_ENMA	  = "Resource/Ace/Event/Enma/mapdata";
const char * FILENAME_EVENT_BUDHA	  = "Resource/Ace/Event/Shaka/mapdata";

WorldPtr World::getTask( ) {
	return std::dynamic_pointer_cast< World >( Application::getInstance( )->getTask( getTag( ) ) );
}

World::World( ) :
_virtue_pos_x( 0 ),
_passed_event( EVENT_NONE ) {
	_map_street = MapPtr( new Map( FILENAME_STREET ) );
	_map_event[ EVENT_REDDAEMON ] = MapPtr( new Map( FILENAME_EVENT_REDDAEMON ) );
	_map_event[ EVENT_FLAME     ] = MapPtr( new Map( FILENAME_EVENT_FIRE      ) );
	_map_event[ EVENT_WOOD      ] = MapPtr( new Map( FILENAME_EVENT_TREE      ) );
	_map_event[ EVENT_MINERAL   ] = MapPtr( new Map( FILENAME_EVENT_ROCK      ) );
	_map_event[ EVENT_SHOP      ] = MapPtr( new Map( FILENAME_EVENT_SHOP      ) );
	_map_event[ EVENT_RYUGU     ] = MapPtr( new Map( FILENAME_EVENT_RYUGU     ) );
	_map_event[ EVENT_LAKE      ] = MapPtr( new Map( FILENAME_EVENT_LAKE      ) );
	_map_event[ EVENT_CALL      ] = MapPtr( new Map( FILENAME_EVENT_GAMBLE	  ) );
	_map_event[ EVENT_GAMBLE    ] = MapPtr( new Map( FILENAME_EVENT_GAMBLE	  ) );
	_map_event[ EVENT_ENMA      ] = MapPtr( new Map( FILENAME_EVENT_ENMA	  ) );
	_map_event[ EVENT_BUDHA     ] = MapPtr( new Map( FILENAME_EVENT_BUDHA	  ) );

}

World::~World( ) {
}

void World::initialize( ) {
	changeEvent( EVENT_NONE );
	_virtue_pos_x = Family::getTask( )->getCameraPosX( );
}

void World::playMapBgm( EVENT type ) {
	SoundPtr sound = Sound::getTask( );
	switch( type ) {
	case EVENT_NONE:
		sound->playBGM( "yokai_music_12.wav" );
		break;
	case EVENT_REDDAEMON:
	case EVENT_FLAME:
	case EVENT_WOOD:
	case EVENT_MINERAL:
		sound->playBGM( "yokai_music_04.wav" );
		break;
	case EVENT_SHOP:
		sound->playBGM( "yokai_music_07.wav" );
		break;
	case EVENT_GAMBLE:
		sound->playBGM( "yokai_music_03.wav" );
		break;
	case EVENT_RYUGU:
		sound->playBGM( "yokai_music_06.wav" );
		break;
	case EVENT_LAKE:
		sound->playBGM( "yokai_music_06.wav" );
		break;
	case EVENT_CALL:
		sound->playBGM( "yokai_music_13.wav", false );
		break;
	case EVENT_ENMA:
		sound->playBGM( "yokai_music_02.wav" );
		break;
	case EVENT_BUDHA:
		sound->playBGM( "yokai_music_08.wav" );
		break;
	}
}


EVENT World::getEvent( ) const {
	return _event->getType( );
}

MapPtr World::getMap( AREA area ) const {
	MapPtr map;

	if ( area == AREA_STREET ) {
		map = _map_street;
	} else {
		map = _map_event[ _event->getType( ) ];
	}
	return map;
}

void World::update( ) {
	updateEvent( );
	updateBGM( );
	updateVirtue( );
}

void World::shiftPos( int map_width ) {
	_virtue_pos_x -= map_width;
}

void World::updateVirtue( ) {
	int camera_x = Family::getTask( )->getCameraPosX( );
	if ( camera_x - _virtue_pos_x > VIRTUE_RANGE ) {
		_virtue_pos_x = camera_x;
		FamilyPtr family( Family::getTask( ) );
		//徳回収モードの場合、徳を出す
		if ( family->isModeVirtue( ) ) {
			StoragePtr storage = Storage::getTask( );
			ItemVirtuePtr virtue( new ItemVirtue( camera_x + 1280 ) );
			storage->add( virtue );
		}
		
	}
}

void World::updateBGM ( ) {
	if ( !Sound::getTask( )->isPlayingBGM( ) ) {
		Sound::getTask( )->playBGM( "yokai_music_12.wav" );
	}
}

void World::updateEvent( ) {
	// イベント更新
	_event->update( );
	_event->fade( );

	KeyboardPtr keyboard = Keyboard::getTask( );

	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		EVENT event = player->getOnEvent( );

		if ( player->isExist( ) ) {
			if ( keyboard->isHoldKey( "1" ) ) event = EVENT_FLAME;
			if ( keyboard->isHoldKey( "2" ) ) event = EVENT_WOOD;
			if ( keyboard->isHoldKey( "3" ) ) event = EVENT_MINERAL;
			if ( keyboard->isHoldKey( "4" ) ) event = EVENT_SHOP;
			if ( keyboard->isHoldKey( "5" ) ) event = EVENT_GAMBLE;
			if ( keyboard->isHoldKey( "6" ) ) event = EVENT_RYUGU;
			if ( keyboard->isHoldKey( "7" ) ) event = EVENT_LAKE;
		}

		// イベントを踏んでいない
		if ( event == EVENT_NONE ) {
			continue;
		}

		// 前回同じイベントだったか？
		if ( _passed_event == event ) {
			continue;
		}

		// 現在イベント
		if ( _event->getType( ) == EVENT_NONE ) {
			// イベントチェンジs
			changeEvent( event );
			_passed_event = event;
		}

		// 別のイベントが実行中
		if ( _event->getType( ) != event ) {
			continue;
		}
		
		// 参加
		_event->join( ( PLAYER )i );
	}
	
	// イベントが終了
	if ( _event->isFinished( ) ) {
		changeEvent( EVENT_NONE );
	}

	// 同期データにイベント情報を設定
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( _event->getType( ) );
}

void World::changeEvent( EVENT type ) {
	// イベント情報を削除
	Military::getTask( )->eraseEventEnemy( );
	Office::getTask( )->eraseEventNPC( );
	Storage::getTask( )->eraseEventItem( );
	Armoury::getTask( )->eraseEventShot( );

	switch ( type ) {
	case EVENT_NONE:
		_event.reset( new EventTitle( ) );
		break;
	case EVENT_REDDAEMON:
		_event.reset( new EventReddaemon( ) );
		break;
	case EVENT_FLAME:
		_event.reset( new EventFlame( ) );
		break;
	case EVENT_WOOD:
		_event.reset( new EventWood( ) );
		break;
	case EVENT_MINERAL:
		_event.reset( new EventMineral( ) );
		break;
	case EVENT_SHOP:
		_event.reset( new EventShop( ) );
		break;
	case EVENT_RYUGU:
		_event.reset( new EventRyugu( ) );
		break;
	case EVENT_LAKE:
		_event.reset( new EventLake( ) );
		break;
	case EVENT_CALL:
		_event.reset( new EventCall( ) );
		break;
	case EVENT_GAMBLE:
		_event.reset( new EventGamble( ) );
		break;
	case EVENT_ENMA:
		_event.reset( new EventEnma( ) );
		break;
	case EVENT_BUDHA:
		_event.reset( new EventBudha( ) );
		break;
	}

	playMapBgm( type );
}