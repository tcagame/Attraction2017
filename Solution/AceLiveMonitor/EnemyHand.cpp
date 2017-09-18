#include "EnemyHand.h"
#include "Military.h"
#include "EnemyHandAttack.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 3;
const int ATTACK_TIME = WAIT_ANIM_TIME * 21;


EnemyHand::EnemyHand( const Vector& pos ) :
Enemy( pos, NORMAL_CHAR_GRAPH_SIZE ) {
	setOverlappedRadius( 36 );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Hand_POWER" ) );
	setForce( property->getData( "Hand_FORCE" ) );
}


EnemyHand::~EnemyHand( ) {
}

void EnemyHand::act( ) {
	const Vector genelate_pos( 35, 40 );
	if ( !( ( getActCount( ) + WAIT_ANIM_TIME * 12 ) % ATTACK_TIME ) ) {
		MilitaryPtr military( Military::getTask( ) );
		Vector origin = getPos( ) - Vector( NORMAL_CHAR_GRAPH_SIZE / 2, NORMAL_CHAR_GRAPH_SIZE );
		military->popUp( EnemyPtr( new EnemyHandAttack( origin  + genelate_pos ) ) );
	}
}

void EnemyHand::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59
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
	if ( getDir( ) == DIR_LEFT ) {
		attribute |= SynchronousData::ATTRIBUTE_REVERSE;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	unsigned char type = getType( );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], attribute, x, y );
}