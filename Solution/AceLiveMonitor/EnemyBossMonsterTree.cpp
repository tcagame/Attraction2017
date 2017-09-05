#include "EnemyBossMonsterTree.h"
#include "EnemyBranch.h"
#include "Military.h"
#include "ItemTree.h"
#include "Storage.h"
#include "SynchronousData.h"

static const int ATTACK_TIME = 50;
static const int MAX_HP = 12;

EnemyBossMonsterTree::EnemyBossMonsterTree( const Vector& pos ) :
EnemyBoss( pos, 192, MAX_HP ) {
	_branch = EnemyPtr( new EnemyBranch( getPos( ) + Vector( -70, -20 ) ) );
	_branch->setArea( AREA_EVENT );
	Military::getTask( )->popUpEventEnemy( _branch );
}


EnemyBossMonsterTree::~EnemyBossMonsterTree( ) {
}

void EnemyBossMonsterTree::act( ) {
}

void EnemyBossMonsterTree::setSynchronousData( unsigned char type, int camera_pos ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, type, 10, 0, x, y, getChipSize( ) );
	
}

void EnemyBossMonsterTree:: dropItem( ) {
	ItemPtr item = ItemPtr( new ItemTree( getPos( ) ) );
	item->setArea( AREA_EVENT );
	Storage::getTask( )->add( item );
}
