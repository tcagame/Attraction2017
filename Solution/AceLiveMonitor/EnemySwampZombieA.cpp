#include "EnemySwampZombieA.h"
#include "SynchronousData.h"
#include "Sound.h"

static const int WAIT_ANIM_TIME = 5;
static const int MAX_HP = 3;

EnemySwampZombieA::EnemySwampZombieA( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 36 );
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingSE( "yokai_voice_04.wav" ) ) {
		sound->getTask( )->playSE( "yokai_voice_04.wav" );
	}
}


EnemySwampZombieA::~EnemySwampZombieA( ) {
}

void EnemySwampZombieA::act( ) {

}

void EnemySwampZombieA::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91
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

void EnemySwampZombieA::damage( int force ) {
}

