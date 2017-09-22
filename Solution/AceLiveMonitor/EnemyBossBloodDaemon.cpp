#include "EnemyBossBloodDaemon.h"
#include "Storage.h"
#include "SynchronousData.h"
#include "Family.h"
#include "Player.h"
#include "Property.h"
#include "EnemyBloodDaemonAttack.h"
#include "Military.h"

const int WAIT_ANIM_TIME = 7;
const int ATTACK_INTERVAL = 60;

EnemyBossBloodDaemon::EnemyBossBloodDaemon( const Vector& pos ) :
EnemyBoss( pos, 128 ) {

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "BloodDaemon_POWER" ) );
	setForce( property->getData( "BloodDaemon_FORCE" ) );
	setOverlappedRadius( property->getData( "BloodDaemon_RADIUS" ) );
}


EnemyBossBloodDaemon::~EnemyBossBloodDaemon( ) {
}

void EnemyBossBloodDaemon::act( ) {
	if ( getActCount( ) % ATTACK_INTERVAL == 0 ) {
		//EnemyPtr attack1 = EnemyPtr( new EnemyBloodDaemonAttack( getPos( ) + Vector( -10, 0 ), 0 ) );
		EnemyPtr attack2 = EnemyPtr( new EnemyBloodDaemonAttack( getPos( ) + Vector( -10, 0 ), 1 ) );
		//attack1->setArea( getArea( ) );
		attack2->setArea( getArea( ) );
		//attack3->setArea( getArea( ) );
		MilitaryPtr military( Military::getTask( ) );
		//military->popUp( attack1 );
		military->popUp( attack2 );
		//military->popUp( attack3 );
	}
}

void EnemyBossBloodDaemon::setSynchronousData( int camera_pos ) const {
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
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, getChipSize( ) );
	
}

void EnemyBossBloodDaemon::dropItem( ) {
	FamilyPtr family( Family::getTask( ) );
	for ( int i = 0; i < MAX_PLAYER; i++ ) {
		PlayerPtr player = family->getPlayer( i );
		if ( player->getArea( ) == AREA_EVENT ) {
			player->pickUpItem( Player::ITEM_FLAME );
		}
	}
}