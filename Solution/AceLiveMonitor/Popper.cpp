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
#include "PopGhost.h"
#include "PopOneEyeSnake.h"
#include "PopWhiteMist.h"
#include "PopStoneFace.h"
#include "PopNoNeckGhost.h"
#include "PopShishimaiDemon.h"
#include "PopShishimai.h"
#include "PopArcher.h"
#include "PopHand.h"
#include "PopRedBird.h"
#include "PopBlueMonk.h"
#include "PopGreenZombie.h"
#include "PopHugDemon.h"
#include "PopSwampZombieA.h"
#include "PopSwampZombieB.h"
#include "PopSwampZombieC.h"

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
			case  OBJECT_GHOST:	
				_pops.push_back( PopPtr( new PopGhost( Vector( x, y ) ) ) );
				break;
			case  OBJECT_ONE_EYE_SNAKE:	
				_pops.push_back( PopPtr( new PopOneEyeSnake( Vector( x, y ) ) ) );
				break;
			case  OBJECT_WHITE_MIST:	
				_pops.push_back( PopPtr( new PopWhiteMist( Vector( x, y ) ) ) );
				break;
			case  OBJECT_STONE_FACE:
				_pops.push_back( PopPtr( new PopStoneFace( Vector( x, y ) ) ) );
				break;
			case  OBJECT_NO_NECK_GHOST:
				_pops.push_back( PopPtr( new PopNoNeckGhost( Vector( x, y ) ) ) );
				break;
			case  OBJECT_SHISHIMAI_DEMON:
				_pops.push_back( PopPtr( new PopShishimaiDemon( Vector( x, y ) ) ) );
				break;
			case  OBJECT_SHISHIMAI:
				_pops.push_back( PopPtr( new PopShishimai( Vector( x, y ) ) ) );
				break;
			case  OBJECT_ARCHER:
				_pops.push_back( PopPtr( new PopArcher( Vector( x, y ) ) ) );
				break;
			case  OBJECT_HAND:
				_pops.push_back( PopPtr( new PopHand( Vector( x, y ) ) ) );
				break;
			case  OBJECT_RED_BIRD:
				_pops.push_back( PopPtr( new PopRedBird( Vector( x, y ) ) ) );
				break;
			case  OBJECT_BLUE_MONK:
				_pops.push_back( PopPtr( new PopBlueMonk( Vector( x, y ) ) ) );
				break;
			case  OBJECT_GREEN_ZOMBIE:
				_pops.push_back( PopPtr( new PopGreenZombie( Vector( x, y ) ) ) );
				break;
			case  OBJECT_HUG_DEMON:
				_pops.push_back( PopPtr( new PopHugDemon( Vector( x, y ) ) ) );
				break;
			case  OBJECT_SWAMP_ZOMBIE_A:
				_pops.push_back( PopPtr( new PopSwampZombieA( Vector( x, y ) ) ) );
				break;
			case  OBJECT_SWAMP_ZOMBIE_B:
				_pops.push_back( PopPtr( new PopSwampZombieB( Vector( x, y ) ) ) );
				break;
			case  OBJECT_SWAMP_ZOMBIE_C:
				_pops.push_back( PopPtr( new PopSwampZombieC( Vector( x, y ) ) ) );
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