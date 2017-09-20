#include "EnemySwampZombieB.h"
#include "SynchronousData.h"
#include "Sound.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;


EnemySwampZombieB::EnemySwampZombieB( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingSE( "yokai_voice_04.wav" ) ) {
		sound->getTask( )->playSE( "yokai_voice_04.wav" );
	}
	

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "SwampZombieB_POWER" ) );
	setForce( property->getData( "SwampZombieB_FORCE" ) );
	setOverlappedRadius( property->getData( "SwampZombieB_RADIUS" ) );
}


EnemySwampZombieB::~EnemySwampZombieB( ) {
}

void EnemySwampZombieB::act( ) {

}

void EnemySwampZombieB::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115
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

void EnemySwampZombieB::damage( int force ) {
}