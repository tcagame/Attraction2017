#include "EnemyBossBloodDaemon.h"
#include "ItemFire.h"
#include "Storage.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 10;
static const int MAX_HP = 12;

EnemyBossBloodDaemon::EnemyBossBloodDaemon( const Vector& pos ) :
EnemyBoss( pos, 128, MAX_HP ) {
}


EnemyBossBloodDaemon::~EnemyBossBloodDaemon( ) {
}

void EnemyBossBloodDaemon::act( ) {

}

void EnemyBossBloodDaemon::setSynchronousData( unsigned char type, int camera_pos ) const {
	const int ANIM[ ] = {
		0, 1, 2, 3
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
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
	
}

void EnemyBossBloodDaemon::dropItem( ) {
	ItemPtr item = ItemPtr( new ItemFire( getPos( ) ) );
	item->setState( STATE_EVENT );
	Storage::getTask( )->add( item );
}