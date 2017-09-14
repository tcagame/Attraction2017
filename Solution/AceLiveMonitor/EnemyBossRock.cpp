#include "EnemyBossRock.h"
#include "ItemRock.h"
#include "Storage.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Player.h"

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
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	//Šâ
	data->addObject( area, type, 0, 0, x, y, getChipSize( ) );
	//“ê
	data->addObject( area, type, 2, 0, x, y, getChipSize( ) );

	
}

void EnemyBossRock::dropItem( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->getArea( ) == AREA_EVENT ) {
			player->pickUpItem( Player::ITEM_MINERAL );
		}
	}
}

