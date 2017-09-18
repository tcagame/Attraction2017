#include "EnemyBossMonsterTree.h"
#include "EnemyBranch.h"
#include "Military.h"
#include "ItemTree.h"
#include "Storage.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Player.h"
#include "Property.h"

const int ATTACK_TIME = 50;

EnemyBossMonsterTree::EnemyBossMonsterTree( const Vector& pos ) :
EnemyBoss( pos, 192 ) {
	EnemyPtr branch = EnemyPtr( new EnemyBranch( getPos( ) + Vector( -70, -20 ) ) );
	branch->setArea( AREA_EVENT );
	Military::getTask( )->popUp( branch );

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "MonsterTree_POWER" ) );
	setForce( property->getData( "MonsterTree_FORCE" ) );
}


EnemyBossMonsterTree::~EnemyBossMonsterTree( ) {
}

void EnemyBossMonsterTree::act( ) {
}

void EnemyBossMonsterTree::setSynchronousData( int camera_pos ) const {
	Vector pos = getPos( );
	int x = ( int )pos.x;
	int y = ( int )pos.y;

	AREA area = AREA_EVENT;
	if ( getArea( ) == AREA_STREET ) {
		x -= camera_pos;
		area = AREA_STREET;
	}
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, 10, 0, x, y, getChipSize( ) );
	
}

void EnemyBossMonsterTree:: dropItem( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->getArea( ) == AREA_EVENT ) {
			player->pickUpItem( Player::ITEM_WOOD );
		}
	}
}
