#include "EnemyArcherAttack.h"
#include "SynchronousData.h"
#include "Property.h"

const Vector MOVE_SPEED( -6, 0 );

EnemyArcherAttack::EnemyArcherAttack( const Vector& pos ) :
Enemy( pos, SMALL_CHAR_GRAPH_SIZE, false ) {
	setVec( MOVE_SPEED );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "ArcherAttack_POWER" ) );
	setForce( property->getData( "ArcherAttack_FORCE" ) );
}

EnemyArcherAttack::~EnemyArcherAttack( ) {
}

void EnemyArcherAttack::act( ) {
}

void EnemyArcherAttack::setSynchronousData( int camera_pos ) const {
	
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
	data->addObject( area, type, 22, attribute, x, y );
}
