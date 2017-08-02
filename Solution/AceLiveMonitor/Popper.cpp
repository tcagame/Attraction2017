#include "Popper.h"
#include "Map.h"
#include "Application.h"
#include "ace_define.h"
#include "Military.h"

#include "PopPurpleZombie.h"
#include "PopFaceAndHand.h"
#include "PopNoFace.h"
#include "PopLancer.h"
#include "PopCrocoSnake.h"
#include "PopGhoul.h"

PopperPtr Popper::getTask( ) {
	return std::dynamic_pointer_cast< Popper >( Application::getInstance( )->getTask( getTag( ) ) );
}

Popper::Popper( ) {
}


Popper::~Popper( ) {
}

void Popper::initialize( ) {
	MapPtr map = Map::getTask( );
	for ( int mx = 0; mx < map->getPageNum( ) * PAGE_OBJECT_WIDTH_NUM; mx++ ) {
		for ( int my = 0; my < OBJECT_CHIP_HEIGHT_NUM; my++ ) {
			unsigned char object = map->getObject( mx, my );
			int x = mx * OBJECT_CHIP_SIZE;
			int y = my * OBJECT_CHIP_SIZE;
			switch ( object ) {
			case  OBJECT_PURPLE_ZOMBIE: 
				_pops.push_back( PopPtr( new PopPurpleZombie( Vector( x, y ) ) ) );
				break;
			case  OBJECT_FACE_AND_HAND:	
				_pops.push_back( PopPtr( new PopFaceAndHand( Vector( x, y ) ) ) );
				break;
			case  OBJECT_NO_FACE:
				_pops.push_back( PopPtr( new PopNoFace( Vector( x, y ) ) ) );
				break;
			case  OBJECT_LANCER:	
				_pops.push_back( PopPtr( new PopLancer( Vector( x, y ) ) ) );
				break;
			case  OBJECT_CROCO_SNAKE:	
				_pops.push_back( PopPtr( new PopCrocoSnake( Vector( x, y ) ) ) );
				break;
			case  OBJECT_GHOUL:	
				_pops.push_back( PopPtr( new PopGhoul( Vector( x, y ) ) ) );
				break;
			}
		}
	}
}

void Popper::update( ) {
	for ( int i = 0; i < _pops.size( ); i++ ) {
		_pops[ i ]->update( );
	}
}