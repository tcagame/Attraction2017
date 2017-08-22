#include "EnemyBossRedDaemon.h"
#include "EnemyLittleRedDaemon.h"
#include "Military.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 10;
static const int WAIT_POP_TIME = 30000;
static const int MAX_HP = 12;
static const int CHIP_SIZE = 256;

EnemyBossRedDaemon::EnemyBossRedDaemon( const Vector& pos ) :
EnemyBoss( pos, CHIP_SIZE, MAX_HP ) {
}


EnemyBossRedDaemon::~EnemyBossRedDaemon( ) {
}

void EnemyBossRedDaemon::act( ) {
	if ( getActCount( ) % WAIT_POP_TIME == 0 ) {
		EnemyPtr enemy = EnemyPtr( new EnemyLittleRedDaemon( getPos( ) + Vector( 100, 0 ) ) );
		enemy->setState( Character::STATE_EVENT );
		Military::getTask( )->popUpEventEnemy( enemy );
	}
}

void EnemyBossRedDaemon::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		8, 9
	};
	int anim_size = sizeof( ANIM ) / sizeof( ANIM[ 0 ] );
	
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	int chip_size = getChipSize( );
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	//–{‘Ì
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, chip_size );
	//˜r
	y -= ( int )( sin( ( double )getActCount( ) / PI * 1 ) * 40 ) - 20;
	data->addObject( area, type, 10, 0, x, y, chip_size );
	
}

void EnemyBossRedDaemon::dropItem( ) {

}
