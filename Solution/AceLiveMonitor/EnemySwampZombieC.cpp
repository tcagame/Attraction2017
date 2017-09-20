#include "EnemySwampZombieC.h"
#include "SynchronousData.h"
#include "Sound.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;


EnemySwampZombieC::EnemySwampZombieC( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	SoundPtr sound = Sound::getTask( );
	if ( !sound->isPlayingSE( "yokai_voice_04.wav" ) ) {
		sound->getTask( )->playSE( "yokai_voice_04.wav" );
	}

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "SwampZombieC_POWER" ) );
	setForce( property->getData( "SwampZombieC_FORCE" ) );
	setOverlappedRadius( property->getData( "SwampZombieC_RADIUS" ) );
}


EnemySwampZombieC::~EnemySwampZombieC( ) {
}

void EnemySwampZombieC::act( ) {

}

void EnemySwampZombieC::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133
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


void EnemySwampZombieC::damage( int force ) {
}