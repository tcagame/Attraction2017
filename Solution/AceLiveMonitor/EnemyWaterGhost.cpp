#include "EnemyWaterGhost.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;

EnemyWaterGhost::EnemyWaterGhost( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "WaterGhost_POWER" ) );
	setForce( property->getData( "WaterGhost_FORCE" ) );
	setOverlappedRadius( property->getData( "WaterGhost_RADIUS" ) );
}


EnemyWaterGhost::~EnemyWaterGhost( ) {
}

void EnemyWaterGhost::act( ) {
}

void EnemyWaterGhost::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = { 340, 341, 342, 343, 344, 345, 346, 347, 348, 349, 350, 351, 352, 353, 354 };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
