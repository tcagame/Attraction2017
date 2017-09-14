#include "RockMapBossCamera.h"
#include "Application.h"
#include "Drawer.h"
#include "RockFamily.h"
#include "RockMapBoss.h"

PTR( RockMapBoss );

const Vector INIT_POS = Vector( 400, 500, -1200 );
const Vector INIT_TARGET = Vector( 400, 125, 0 );
const Vector STREET_DIR = Vector( 0, 0.8, -1 ).normalize( );
const Vector BOSS_DIR = Vector( -1, 0.5, 0 ).normalize( );
const double LENGTH = 300;

RockMapBossCamera::RockMapBossCamera( ) :
RockCamera( INIT_POS, INIT_TARGET ) {
}

RockMapBossCamera::~RockMapBossCamera( ) {
}

void RockMapBossCamera::setCamera( ) {
	Vector target = RockFamily::getTask( )->getCameraPos( );
	RockMapBossPtr map = std::dynamic_pointer_cast< RockMapBoss >( RockMapBoss::getTask( ) );
	RockMapBoss::STAGE stage = map->getStage( );

	if ( target.isOrijin( ) ) {
		setPos( INIT_POS );
		setTarget( INIT_TARGET );
	} else {
		Vector pos;
		switch( stage ) {
		case RockMapBoss::STAGE_FIRE:
		case RockMapBoss::STAGE_ROCK:
		case RockMapBoss::STAGE_TREE:
			target = Vector( -18.5, 0, -19.5 );
			pos = target + BOSS_DIR * LENGTH;
			break;
		case RockMapBoss::STAGE_FIRE_TO_ROCK:
		case RockMapBoss::STAGE_ROCK_TO_TREE:
		case RockMapBoss::STAGE_TREE_TO_FIRE:
			pos = target + STREET_DIR * LENGTH;
			break;
		}
		setPos( pos );
		setTarget( target );
	}
}
