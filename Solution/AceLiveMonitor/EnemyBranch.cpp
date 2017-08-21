#include "EnemyBranch.h"
#include "EnemySeed.h"
#include "Military.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int ATTACK_TIME = WAIT_ANIM_TIME * 11;
static const int MAX_HP = 3;

EnemyBranch::EnemyBranch( const Vector& pos ) :
EnemyAttack( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setRadius( 36 );
}

EnemyBranch::~EnemyBranch( ) {
	_seeds.clear( );
}

void EnemyBranch::act( ) {
	if ( !( ( getActCount( ) + WAIT_ANIM_TIME * 5 ) % ATTACK_TIME ) ) {
		EnemyPtr seed( new EnemySeed( getPos( ) ) );
		seed->setState( STATE_EVENT );
		_seeds.push_back( seed );
		Military::getTask( )->popUpEventEnemy( seed );
	}
}

void EnemyBranch::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = { 68, 69, 70, 71, 72, 73, 74, 71, 70, 79, 68  };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_MAIN ) {
		x -= camera_pos;
		area = AREA_MAIN;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
}