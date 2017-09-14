#include "World.h"
#include "Map.h"
#include "SynchronousData.h"
#include "Application.h"
#include "Sound.h"


static const char * FILENAME_STREET          = "Resource/Ace/Street/mapdata";
static const char * FILENAME_EVENT_REDDAEMON = "Resource/Ace/Event/Reddaemon/mapdata";
static const char * FILENAME_EVENT_FIRE      = "Resource/Ace/Event/Fire/mapdata";
static const char * FILENAME_EVENT_TREE      = "Resource/Ace/Event/Tree/mapdata";
static const char * FILENAME_EVENT_ROCK      = "Resource/Ace/Event/Rock/mapdata";
static const char * FILENAME_EVENT_SHOP      = "Resource/Ace/Event/Shop/mapdata";
static const char * FILENAME_EVENT_RYUGU     = "Resource/Ace/Event/Ryugu/mapdata"; 
static const char * FILENAME_EVENT_LAKE      = "Resource/Ace/Event/Lake/mapdata";
static const char * FILENAME_EVENT_GAMBLE	 = "Resource/Ace/Event/Gamble/mapdata";

WorldPtr World::getTask( ) {
	return std::dynamic_pointer_cast< World >( Application::getInstance( )->getTask( getTag( ) ) );
}

World::World( ) :
_event( EVENT_NONE ) {
	_map_street = MapPtr( new Map( FILENAME_STREET ) );
	_map_event[ EVENT_REDDAEMON ] = MapPtr( new Map( FILENAME_EVENT_REDDAEMON ) );
	_map_event[ EVENT_FLAME      ] = MapPtr( new Map( FILENAME_EVENT_FIRE      ) );
	_map_event[ EVENT_WOOD      ] = MapPtr( new Map( FILENAME_EVENT_TREE      ) );
	_map_event[ EVENT_MINERAL      ] = MapPtr( new Map( FILENAME_EVENT_ROCK      ) );
	_map_event[ EVENT_SHOP      ] = MapPtr( new Map( FILENAME_EVENT_SHOP      ) );
	_map_event[ EVENT_RYUGU     ] = MapPtr( new Map( FILENAME_EVENT_RYUGU     ) );
	_map_event[ EVENT_LAKE      ] = MapPtr( new Map( FILENAME_EVENT_LAKE      ) );
	_map_event[ EVENT_GAMBLE    ] = MapPtr( new Map( FILENAME_EVENT_GAMBLE	  ) );

	Sound::getTask( )->playBGM( "yokai_music_12.wav" );
}

World::~World( ) {
}

void World::initialize( ) {
}

void World::update( ) {
	// 同期データにイベント情報を設定
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->setEvent( _event );
}

void World::setEvent( EVENT event ) {
	_event = event;
	playMapBgm( _event );
}

void World::playMapBgm( EVENT event ) {
	SoundPtr sound = Sound::getTask( );
	switch( _event ) {
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
	}
}


EVENT World::getEvent( ) const{
	return _event;
}

MapPtr World::getMap( AREA area ) const {
	MapPtr map;

	if ( area == AREA_STREET ) {
		map = _map_street;
	} else {
		map = _map_event[ _event ];
	}

	return map;
}