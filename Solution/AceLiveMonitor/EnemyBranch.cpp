#include "EnemyBranch.h"
#include "EnemySeed.h"
#include "Military.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 5;
static const int ATTACK_TIME = WAIT_ANIM_TIME * 10;
static const int MAX_HP = 3;

EnemyBranch::EnemyBranch( const Vector& pos ) :
EnemyAttack( pos, NORMAL_CHAR_GRAPH_SIZE, MAX_HP, false ) {
	setOverlappedRadius( 36 );
}

EnemyBranch::~EnemyBranch( ) {
}

void EnemyBranch::act( ) {
	if ( !( ( getActCount( ) + WAIT_ANIM_TIME * 5 ) % ATTACK_TIME ) ) {
		EnemyPtr seed( new EnemySeed( getPos( ) ) );
		seed->setArea( AREA_EVENT );
		Military::getTask( )->popUp( seed );
	}
}

void EnemyBranch::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = { 99, 100, 101, 102, 103, 104, 105, 101, 100, 99  };
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
}