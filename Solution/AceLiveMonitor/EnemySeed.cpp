#include "EnemySeed.h"
#include "Military.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int ATTACK_TIME = WAIT_ANIM_TIME * 11;
static const int JUMP_MAX_HP = -15;
static const int MAX_HP = 2;

EnemySeed::EnemySeed( const Vector& pos ) :
EnemyAttack( pos, SMALL_CHAR_GRAPH_SIZE, MAX_HP ) {
	setRadius( 16 );
	setVec( Vector( -10, 0 ) );
}

EnemySeed::~EnemySeed( ) {
}

void EnemySeed::act( ) {
	if ( isStanding( ) ) setVec( getVec( ) + Vector( 0, JUMP_MAX_HP ) );
}

void EnemySeed::setSynchronousData( unsigned char type, int camera_pos ) const {
	int anim = 278;
	if ( isStanding( ) ) {
		anim++;
	}
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, anim, 0, x, y, getChipSize( ) );
	
}