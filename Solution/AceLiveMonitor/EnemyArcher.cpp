#include "EnemyArcher.h"
#include "EnemyArcherAttack.h"
#include "Military.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int MOVE_SPEED = -2;
const int MOVE_TIME = WAIT_ANIM_TIME * 9;
const int ANIM_LOOP_TIME = WAIT_ANIM_TIME * 18;
const int SHOT_TIMING = ( MOVE_TIME + WAIT_ANIM_TIME * 5 ) - 2;

EnemyArcher::EnemyArcher( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ),
_act( ACTION_MOVE ) {
	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Archer_POWER" ) );
	setForce( property->getData( "Archer_FORCE" ) );
	setOverlappedRadius( property->getData( "Archer_RADIUS" ) );
}

EnemyArcher::~EnemyArcher( ) {
}

void EnemyArcher::act( ) {
	setVec( Vector( MOVE_SPEED, getVec( ).y ) );
	if ( ( getActCount( ) % ( ANIM_LOOP_TIME - 2 ) ) >= MOVE_TIME ) {
		setVec( Vector( ) );
	}
	if ( ( getActCount( ) % ANIM_LOOP_TIME ) == SHOT_TIMING ) {
		Military::getTask( )->popUp( EnemyPtr( new EnemyArcherAttack( getPos( ) + Vector( -11, -18, 0 ) ) ) );
	}
}

void EnemyArcher::setSynchronousData( int camera_pos ) const {
	int ANIM[ ] = { /*move*/ 300, 301, 302, 303, 304, 305, 306, 307, 308, /*shot*/ 309, 310, 311, 312, 313, 314, 315, 316, 317 };
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

