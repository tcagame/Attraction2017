#include "EnemyRedBird.h"
#include "EnemyRedBirdAttack.h"
#include "Military.h"
#include "SynchronousData.h"
#include "Sound.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 4;
const int ATTACK_TIME = 30;
const int MOVE_SPEED = -5;

EnemyRedBird::EnemyRedBird( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, false ) {
	setOverlappedRadius( 36 );
	Sound::getTask( )->playSE( "yokai_voice_02.wav" );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "RedBird_POWER" ) );
	setForce( property->getData( "RedBird_FORCE" ) );
}


EnemyRedBird::~EnemyRedBird( ) {
}

void EnemyRedBird::act( ) {
	setVec( Vector( MOVE_SPEED, 0 ) );
	if ( !( getActCount( ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		military->popUp( EnemyPtr( new EnemyRedBirdAttack( getPos( ) ) ) );
	}
}

void EnemyRedBird::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		320, 321, 322, 323, 324, 325, 326, 327, 328, 329
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
