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


static const char * FILENAME_STREET          = "Resource/Ace/Street/mapdata";
static const char * FILENAME_EVENT_REDDAEMON = "Resource/Ace/Event/Reddaemon/mapdata";
static const char * FILENAME_EVENT_FIRE      = "Resource/Ace/Event/Fire/mapdata";
static const char * FILENAME_EVENT_TREE      = "Resource/Ace/Event/Tree/mapdata";
static const char * FILENAME_EVENT_ROCK      = "Resource/Ace/Event/Rock/mapdata";
static const char * FILENAME_EVENT_SHOP      = "Resource/Ace/Event/Shop/mapdata";
static const char * FILENAME_EVENT_RYUGU     = "Resource/Ace/Event/Ryugu/mapdata"; 
static const char * FILENAME_EVENT_LAKE      = "Resource/Ace/Event/Lake/mapdata";
static const char * FILENAME_EVENT_CALL 	 = "Resource/Ace/Event/Call/mapdata";
static const char * FILENAME_EVENT_GAMBLE	 = "Resource/Ace/Event/Gamble/mapdata";

WorldPtr World::getTask( ) {
	return std::dynamic_pointer_cast< World >( Application::getInstance( )->getTask( getTag( ) ) );
}

World::World( ) {
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

}

World::~World( ) {
}

void World::initialize( ) {
	changeEvent( EVENT_NONE );
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
	if ( !map ) {
		int check = -1;
	}
	return map;
}

void World::update( ) {
	updateEvent( );
	updateBGM( );
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

	// イベントが終了
	if ( _event->isFinished( ) ) {
		changeEvent( EVENT_NONE );
	}

	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		EVENT event = player->getOnEvent( );

		// イベントを踏んでいない
		if ( event == EVENT_NONE ) {
			continue;
		}

		// 現在イベント
		if ( _event->getType( ) == EVENT_NONE ) {
			// イベントチェンジ
			changeEvent( event );
		}

		// 別のイベントが実行中
		if ( _event->getType( ) != event ) {
			continue;
		}
		
		// 現在参加できない
		if ( !_event->isJoining( ) ) {
			return;
		}

		// 参加
		_event->join( ( PLAYER )i );
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
	}

	playMapBgm( type );
}