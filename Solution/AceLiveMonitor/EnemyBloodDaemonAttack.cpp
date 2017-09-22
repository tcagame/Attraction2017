#include "EnemyBloodDaemonAttack.h"
#include "SynchronousData.h"

const int MAX_SPEED = 8;
const int WAIT_ANIM_TIME = 3;

EnemyBloodDaemonAttack::EnemyBloodDaemonAttack( const Vector& pos, int pattern ) :
EnemyAttack( pos, 64, false ) {
	switch ( pattern ) {
	case 0:
		//左斜め上
		setVec( Vector( -1, -0.3 ).normalize( ) * MAX_SPEED );
		break;
	case 1:
		//左
		setVec( Vector( -1, 0 ).normalize( ) * MAX_SPEED );
		break;
	case 2:
		//左下
		setVec( Vector( -1, 0.3 ).normalize( ) * MAX_SPEED );
		break;
	default:
		setVec( Vector( -1, 0 ).normalize( ) * MAX_SPEED );
		pattern = 1;
	}
	_pattern = pattern;
	setOverlappedRadius( 32 );
	setPower( 2 );
	setForce( 2 );
}


EnemyBloodDaemonAttack::~EnemyBloodDaemonAttack( ) {
}

void EnemyBloodDaemonAttack::act( ) {
	if ( getPos( ).y > GRAPH_SIZE - 30 ) {
		if ( getVec( ).y > 0 ) {
			setVec( getVec( ) + Vector( 0, -0.3 ) );
		}
	}
}

void EnemyBloodDaemonAttack::setSynchronousData( int camera_pos ) const {
	//size:64
	//アニメーション数:8x3
	//場所:3段目の12から

	int off = 32 * 3 + 12;
	const int ANIM[ ] = {
		off + 0, off + 1, off + 2, off + 3, off + 4, off + 5, off + 6, off + 7
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	int anim = off;
	switch ( _pattern ) {
	case 0:
		anim = off + 32 * 2 + 1;
		break;
	default:
		anim = off + 32 * 2;
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
	//ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ]
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, anim, 0, x, y, 64 );
	
}
