#include "World.h"
#include "Map.h"
#include "SynchronousData.h"
#include "Application.h"

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
	_map_event[ EVENT_FIRE      ] = MapPtr( new Map( FILENAME_EVENT_FIRE      ) );
	_map_event[ EVENT_TREE      ] = MapPtr( new Map( FILENAME_EVENT_TREE      ) );
	_map_event[ EVENT_ROCK      ] = MapPtr( new Map( FILENAME_EVENT_ROCK      ) );
	_map_event[ EVENT_SHOP      ] = MapPtr( new Map( FILENAME_EVENT_SHOP      ) );
	_map_event[ EVENT_RYUGU     ] = MapPtr( new Map( FILENAME_EVENT_RYUGU     ) );
	_map_event[ EVENT_LAKE      ] = MapPtr( new Map( FILENAME_EVENT_LAKE      ) );
	_map_event[ EVENT_GAMBLE    ] = MapPtr( new Map( FILENAME_EVENT_GAMBLE	  ) );
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