#include "EnemyBossRock.h"
#include "ItemRock.h"
#include "Storage.h"

static const int MAX_HP = 12;

EnemyBossRock::EnemyBossRock( const Vector& pos ) :
EnemyBoss( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP ) {
}


EnemyBossRock::~EnemyBossRock( ) {
}

void EnemyBossRock::act( ) {

}

Chip EnemyBossRock::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 512;
	chip.ty = 0;
	return chip;
}

Chip EnemyBossRock::getChip2( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = getChipSize( );
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 896;
	chip.ty = 0;
	return chip;
}

void EnemyBossRock::dropItem( ) {
	ItemPtr item = ItemPtr( new ItemRock( getPos( ) ) );
	item->setState( STATE_EVENT );
	Storage::getTask( )->add( item );
}

