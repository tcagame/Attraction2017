#include "EnemyBossMonsteTree.h"
#include "EnemyBranch.h"
#include "Military.h"
#include "ItemTree.h"
#include "Storage.h"

static const int ATTACK_TIME = 50;
static const int MAX_HP = 12;

EnemyBossMonsteTree::EnemyBossMonsteTree( const Vector& pos ) :
EnemyBoss( pos, BIG_CHAR_GRAPH_SIZE, MAX_HP ) {
	_branch = EnemyPtr( new EnemyBranch( getPos( ) + Vector( -70, -20 ) ) );
	_branch->setState( Character::STATE_EVENT );
	Military::getTask( )->popUpEventEnemy( _branch );
}


EnemyBossMonsteTree::~EnemyBossMonsteTree( ) {
	_branch->isFinished( );
	ItemPtr item = ItemPtr( new ItemTree( getPos( ) ) );
	item->setState( STATE_EVENT );
	Storage::getTask( )->add( item );
}

void EnemyBossMonsteTree::act( ) {
}

Chip EnemyBossMonsteTree::getChip( ) const {
	Chip chip = Chip( );
	Vector pos = getPos( );
	chip.size = 192;
	chip.sx1 = ( int )pos.x - chip.size / 2;
	chip.sy1 = ( int )pos.y - chip.size;
	chip.sx2 = chip.sx1 + chip.size;
	chip.sy2 = chip.sy1 + chip.size;
	chip.tx = 0;
	chip.ty = 128;
	return chip;
}
