#include "EnemyTree.h"
#include "Military.h"
#include "EnemyTreeNuts.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int CHIP_SIZE = 192;
const int ATTACK_TIME = 30;
const int MAX_GENERATE_NUM = 9;

const Vector GENERATE_POS[ MAX_GENERATE_NUM ] = {
	Vector( 6, 850 - 736 ),
	Vector( 12, 875 - 736 ),
	Vector( 45, 876 - 736 ),
	Vector( 84, 822 - 736 ),
	Vector( 126, 796 - 736 ),
	Vector( 176, 810 - 736 ),
	Vector( 175, 849 - 736 ),
	Vector( 159, 864 - 736 ),
	Vector( 142, 874 - 736 )
};

EnemyTree::EnemyTree( const Vector& pos ) :
Enemy( pos, CHIP_SIZE ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Tree_POWER" ) );
	setForce( property->getData( "Tree_FORCE" ) );
	setOverlappedRadius( property->getData( "Tree_RADIUS" ) );
}


EnemyTree::~EnemyTree( ) {
}

void EnemyTree::act( ) {
	if ( !( getActCount( ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		Vector origin = getPos( ) - Vector( CHIP_SIZE / 2, CHIP_SIZE );
		military->popUp( EnemyPtr( new EnemyTreeNuts( origin + GENERATE_POS[ rand( ) % 9 ] ) ) );
	}
}

void EnemyTree::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		36, 37
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BIG, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
	
}