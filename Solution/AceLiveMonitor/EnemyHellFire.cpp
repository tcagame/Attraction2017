#include "EnemyHellFire.h"
#include "Family.h"
#include "Player.h"
#include "SynchronousData.h"
#include "Property.h"

const double MOVE_SPEED = 3;
const double ACCEL = 0.5;
const int WAIT_ANIM_TIME = 4;

EnemyHellFire::EnemyHellFire( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
	
	/*
	setPower( property->getData( "HellFire_POWER" ) );
	*/
	PropertyPtr property( Property::getTask( ) );
	setForce( property->getData( "HellFire_FORCE" ) );
	setOverlappedRadius( property->getData( "HellFire_RADIUS" ) );
}


EnemyHellFire::~EnemyHellFire( ) {
}

void EnemyHellFire::act( ) {
	Vector target = Vector( Family::getTask( )->getCameraPosX( ) + GRAPH_SIZE, GRAPH_SIZE / 2 );
	FamilyPtr family( Family::getTask( ) );
	//���u�v���C���[��_��
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( !player->isExist( ) ) {
			continue;
		}
		if ( player->isLeaveAlone( ) ) {
			target = player->getPos( );
			return;
		}
	}
	Vector distance = target - getPos( );
	Vector vec = getVec( ) + distance.normalize( ) * ACCEL;
	vec = vec.normalize( ) * MOVE_SPEED;
	setVec( vec );
}

void EnemyHellFire::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		360, 361, 362, 363, 364, 365, 366, 367, 368, 369,
		370, 371, 372, 373, 374, 375, 376, 377, 378, 379,
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
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
