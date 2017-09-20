#include "EnemySwampZombieA.h"
#include "SynchronousData.h"
#include "Sound.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;


EnemySwampZombieA::EnemySwampZombieA( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingSE( "yokai_voice_04.wav" ) ) {
		sound->getTask( )->playSE( "yokai_voice_04.wav" );
	}

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "SwampZombieA_POWER" ) );
	setForce( property->getData( "SwampZombieA_FORCE" ) );
	setOverlappedRadius( property->getData( "SwampZombieA_RADIUS" ) );
}


EnemySwampZombieA::~EnemySwampZombieA( ) {
}

void EnemySwampZombieA::act( ) {

}

void EnemySwampZombieA::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93
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

void EnemySwampZombieA::damage( int force ) {
}

