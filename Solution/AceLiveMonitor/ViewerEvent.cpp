#include "ViewerEvent.h"
#include "Drawer.h"
#include "ace_define.h"
#include "Family.h"
#include "MapEvent.h"
#include "NPC.h"

ViewerEvent::ViewerEvent( ) {
	DrawerPtr drawer( Drawer::getTask( ) );
	_frame = drawer->createImage( "Event/event_frame.png");

	char buf[ 256 ];
	//TITLE
	_images.push_back( drawer->createImage( "Event/title_logo.png" ) );
	//RED_DAEMON
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/akaoni/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//FIRE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/fire/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//TREE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/tree/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//ROCK
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/rock/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//SHOP
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/shop/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//RYUGU
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/ryugu/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	//LAKE
	for ( int i = 0; i < EVENT_PAGE_NUM; i++ ) {
		sprintf_s( buf, "Event/lake/back_%003d.png", i );
		_images.push_back( drawer->createImage( buf ) );
	}
	_characters = drawer->createImage( "Event/character/character.png" );

}

ViewerEvent::~ViewerEvent( ) {
}

void ViewerEvent::draw( ) const {
	MapEventPtr map( MapEvent::getTask( ) );
	MapEvent::TYPE type = map->getType( );
	if( type == MapEvent::TYPE_TITLE ) {
		_images[ 0 ]->setPos( 0, VIEW_TITLE_Y );
		_images[ 0 ]->draw( );
	} else {
		int idx = 0;
		int sx = 256;
		for ( int i = 0; i < 8; i++ ) {
			switch ( type ) {
			case MapEvent::TYPE_RED_DAEMON:
				idx = type + ( i % EVENT_PAGE_NUM );
				break;
			case MapEvent::TYPE_FIRE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
			case MapEvent::TYPE_TREE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_ROCK:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_SHOP:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_RYUGU:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			case MapEvent::TYPE_LAKE:
				if ( i / EVENT_PAGE_NUM > 0 ) {
					idx = type + 3; 
				} else {
					idx = type + i;
				}
				break;
			}
			_images[ idx ]->setPos( i * sx, VIEW_TITLE_Y );
			_images[ idx ]->draw( );
		}
		{// npc chara
			FamilyConstPtr family( Family::getTask( ) );
			int camera_pos = ( int )family->getCameraPos( );
			NPCPtr npc( NPC::getTask( ) );
			std::list< CharacterPtr > chara_list = npc->getNPCChara( );
			std::list< CharacterPtr >::const_iterator ite = chara_list.begin( );
			while( ite != chara_list.end( ) ) {
				if ( !( *ite ) ) {
					ite++;
					continue;
				}
				CharacterPtr chara = ( *ite );
				Chip chip = chara->getChip( );
				chip.sy1 += VIEW_EVENT_Y;
				chip.sy2 += VIEW_EVENT_Y;
				_characters->setRect( chip.tx, chip.ty, chip.size, chip.size );
				_characters->setPos( chip.sx1, chip.sy1, chip.sx2, chip.sy2 );
				_characters->draw( );
				ite++;
			}
		}
	}
	_frame->setPos( 0, VIEW_TITLE_Y );
	_frame->draw( );
}