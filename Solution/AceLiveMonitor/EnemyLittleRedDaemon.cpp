#include "EnemyLittleRedDaemon.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 6;

EnemyLittleRedDaemon::EnemyLittleRedDaemon( const Vector& pos ):
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "LittleRedDaemon_POWER" ) );
	setForce( property->getData( "LittleRedDaemon_FORCE" ) );
	setOverlappedRadius( property->getData( "LittleRedDaemon_RADIUS" ) );
}


EnemyLittleRedDaemon::~EnemyLittleRedDaemon( ) {
}

void EnemyLittleRedDaemon::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		393, 394, 395, 396, 397
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
	unsigned char attribute = 0;
	if ( getDir( ) == DIR_RIGHT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y, getChipSize( ) );
}

void EnemyLittleRedDaemon::act( ) {
	setVec( Vector( -3, 0 ) );
}