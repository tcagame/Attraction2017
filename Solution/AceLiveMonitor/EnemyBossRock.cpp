#include "EnemyBossRock.h"
#include "ItemRock.h"
#include "Storage.h"
#include "SynchronousData.h"

static const int MAX_HP = 12;

EnemyBossRock::EnemyBossRock( const Vector& pos ) :
EnemyBoss( pos, 128, MAX_HP ) {
}


EnemyBossRock::~EnemyBossRock( ) {
}

void EnemyBossRock::act( ) {

}

void EnemyBossRock::setSynchronousData( unsigned char type, int camera_pos ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getState( ) == STATE_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	//Šâ
	data->addObject( area, type, 4, 0, x, y, getChipSize( ) );
	//“ê
	data->addObject( area, type, 7, 0, x, y, getChipSize( ) );

	
}

void EnemyBossRock::dropItem( ) {
	ItemPtr item = ItemPtr( new ItemRock( getPos( ) ) );
	item->setState( STATE_EVENT );
	Storage::getTask( )->add( item );
}

