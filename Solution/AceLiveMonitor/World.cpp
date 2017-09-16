#include "World.h"
#include "Map.h"
#include "SynchronousData.h"
#include "Application.h"
#include "Sound.h"
#include "Family.h"
#include "Player.h"

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

	Sound::getTask( )->playBGM( "yokai_music_12.wav" );
}

World::~World( ) {
}

void World::initialize( ) {
	setEvent( EVENT_TITLE );
}

void World::setEvent( EVENT type ) {
	_event->reset( );

	switch ( type ) {
	case EVENT_TITLE:
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

void World::playMapBgm( EVENT type ) {
	SoundPtr sound = Sound::getTask( );
	switch( type ) {
	case EVENT_TITLE:
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
		/*
		メインテーマで前奏が長くドロドロしている雰囲気のBGMがある
		コールではそのＢＧＭを流し、前奏がもんもたろーのテーマとおもわせる
		そしてそのままメインテーマがながれるので、ここからタイトルに移った場合はBGMを再生させないようにする
		*/
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

	onEvent( );
	updateEvent( );

	// 同期データにイベント情報を設定
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( _event->getType( ) );
}

void World::updateEvent( ) {
	FamilyPtr family( Family::getTask( ) );
	if ( !family->isExistOnEvent( ) ) {
		setEvent( EVENT_TITLE );
	}

	_event->update( );
}

void World::onEvent( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		EVENT event = player->getOnEvent( );
		switch ( event ) {
		case EVENT_REDDAEMON:
			onEventReddaemon( player );
			break;
		case EVENT_FLAME:
			onEventFlame( player );
			break;
		case EVENT_WOOD:
			onEventWood( player );
			break;
		case EVENT_MINERAL:
			onEventMineral( player );
			break;
		case EVENT_SHOP:
			onEventShop( player );
			break;
		case EVENT_RYUGU:
			onEventRyugu( player );
			break;
		case EVENT_LAKE:
			onEventLake( player );
			break;
		case EVENT_CALL:
			onEventCall( player );
			break;
		case EVENT_GAMBLE:
			onEventGamble( player );
			break;
		}
	}
}


void World::onEventReddaemon( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_REDDAEMON ) {
		return;
	}
	if ( _event->getType( ) != EVENT_REDDAEMON ) {
		setEvent( EVENT_REDDAEMON );
	}
	player->enterEvent( );
}

void World::onEventFlame( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_FLAME ) {
		return;
	}
	if ( _event->getType( ) != EVENT_FLAME ) {
		setEvent( EVENT_FLAME );
	}
	player->enterEvent( );
}

void World::onEventWood( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_WOOD ) {
		return;
	}
	if ( _event->getType( ) != EVENT_WOOD ) {
		setEvent( EVENT_WOOD );
	}
	player->enterEvent( );
}

void World::onEventMineral( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_MINERAL ) {
		return;
	}
	if ( _event->getType( ) != EVENT_TITLE ) {
		setEvent( EVENT_MINERAL );
	}
	player->enterEvent( );
}

void World::onEventShop( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_SHOP ) {
		return;
	}
	if ( _event->getType( ) != EVENT_SHOP ) {
		setEvent( EVENT_SHOP );
	}
	player->enterEvent( );
}

void World::onEventRyugu( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_RYUGU ) {
		return;
	}
	if ( _event->getType( ) != EVENT_RYUGU ) {
		setEvent( EVENT_RYUGU );
	}
	player->enterEvent( );
}

void World::onEventLake( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_LAKE ) {
		return;
	}
	if ( _event->getType( ) != EVENT_LAKE ) {
		setEvent( EVENT_LAKE );
	}
	player->enterEvent( );
}

void World::onEventCall( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_CALL ) {
		return;
	}
	if ( _event->getType( ) != EVENT_CALL ) {
		setEvent( EVENT_CALL );
	}
	player->enterEvent( );
	//Sound::getTask( )->playSE( "yokai_voice_06.wav" );
	//player->setAction( ACTION_CALL );
	//player->setVec( Vector( ) );
}

void World::onEventGamble( PlayerPtr player ) {
	if ( _event->getType( ) != EVENT_TITLE && _event->getType( ) != EVENT_GAMBLE ) {
		return;
	}
	if ( _event->getType( ) != EVENT_GAMBLE ) {
		setEvent( EVENT_GAMBLE );
	}
	player->enterEvent( );
}

/*
		}

		if ( map->getObject( _player[ i ]->getPos( ) + _player[ i ]->getVec( ) ) == OBJECT_EVENT_CALL ) {
		}

		if ( _player[ i ]->getArea( ) == AREA_EVENT ) {
			//一ページ目にいたらメインに戻る
			}
			//ボスが倒れている場合 && アイテムが無い[退場]
			StoragePtr storage( Storage::getTask( ) );
			if ( !Military::getTask( )->getBoss( ) &&
				 !storage->isExistanceEventItem( ) &&
				 world->getEvent( ) < EVENT_SHOP ) {
				_player[ i ]->setArea( AREA_STREET );
				world->setEvent( EVENT_NONE );
				militaly->eraseEventEnemy( );
				_player[ i ]->setPos( Vector( family->getCameraPosX( ) + SCREEN_WIDTH / 2, 0 ) );
				_player[ i ]->setVec( Vector( ) );
			}
		}
	}
}
*/