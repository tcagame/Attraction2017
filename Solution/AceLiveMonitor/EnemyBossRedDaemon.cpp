#include "EnemyBossRedDaemon.h"
#include "EnemyLittleRedDaemon.h"
#include "Military.h"
#include "SynchronousData.h"
#include "Property.h"

const int WAIT_ANIM_TIME = 10;
const int WAIT_POP_TIME = 300;
const int CHIP_SIZE = 192;

EnemyBossRedDaemon::EnemyBossRedDaemon( const Vector& pos ) :
EnemyBoss( pos, CHIP_SIZE ) {

	PropertyPtr property( Property::getTask( ) );
	setPower( property->getData( "RedDaemon_POWER" ) );
	setForce( property->getData( "RedDaemon_FORCE" ) );
	setOverlappedRadius( property->getData( "RedDaemon_RADIUS" ) );
}


EnemyBossRedDaemon::~EnemyBossRedDaemon( ) {
}

void EnemyBossRedDaemon::act( ) {
	if ( getActCount( ) % WAIT_POP_TIME == 0 ) {
		EnemyPtr enemy = EnemyPtr( new EnemyLittleRedDaemon( getPos( ) + Vector( 100, 0 ) ) );
		enemy->setArea( AREA_EVENT );
		Military::getTask( )->popUp( enemy );
	}
}

void EnemyBossRedDaemon::setSynchronousData( int camera_pos ) const {
	const int ANIM[ ] = {
		40, 41
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
	int chip_size = getChipSize( );
	SynchronousDataPtr data( SynchronousData::getTask( ) );
	//–{‘Ì
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, ANIM[ getActCount( ) / WAIT_ANIM_TIME % anim_size ], 0, x, y, chip_size );
	//˜r
	y -= ( int )( sin( ( double )getActCount( ) / PI * 1 ) * 40 ) - 20;
	data->addObject( area, SynchronousData::TYPE_ENEMY_BOSS, 42, 0, x, y, chip_size );
	
}

void EnemyBossRedDaemon::dropItem( ) {

}
