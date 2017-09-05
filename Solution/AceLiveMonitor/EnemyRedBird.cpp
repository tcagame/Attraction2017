#include "EnemyRedBird.h"
#include "EnemyRedBirdAttack.h"
#include "Military.h"
#include "SynchronousData.h"
#include "Sound.h"

const int WAIT_ANIM_TIME = 5;
const int ATTACK_TIME = 30;
const int MAX_HP = 3;
const int MOVE_SPEED = -5;

EnemyRedBird::EnemyRedBird( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 36 );
	Sound::getTask( )->playSE( "yokai_voice_02.wav" );
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

void EnemyRedBird::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		280, 281, 282, 283, 284, 285, 286, 287, 288, 289
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
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}
