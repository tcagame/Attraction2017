#include "EnemyBossBloodDaemon.h"
#include "ItemFire.h"
#include "Storage.h"
#include "SynchronousData.h"

static const int WAIT_ANIM_TIME = 7;
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
		48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
		64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78
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
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
	
}

void EnemyBossBloodDaemon::dropItem( ) {
	ItemPtr item = ItemPtr( new ItemFire( getPos( ) ) );
	item->setArea( AREA_EVENT );
	Storage::getTask( )->add( item );
}