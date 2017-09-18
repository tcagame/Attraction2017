#include "EnemySeed.h"
#include "Military.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 5;
const int ATTACK_TIME = WAIT_ANIM_TIME * 11;
const int JUMP_MAX_HP = -15;

EnemySeed::EnemySeed( const Vector& pos ) :
EnemyAttack( pos, SMALL_CHAR_GRAPH_SIZE ) {
	setOverlappedRadius( 16 );
	setVec( Vector( -10, 0 ) );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "Seed_POWER" ) );
	setForce( property->getData( "Seed_FORCE" ) );
}

EnemySeed::~EnemySeed( ) {
}

void EnemySeed::act( ) {
	if ( isStanding( ) ) setVec( getVec( ) + Vector( 0, JUMP_MAX_HP ) );
}

void EnemySeed::setSynchronousData( int camera_pos ) const {
	int anim = 405;
	if ( isStanding( ) ) {
		anim++;
	}
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, anim, 0, x, y, getChipSize( ) );
	
}