#include "RockEnemy.h"
#include "RockPlayer.h"
#include "RockDollHouse.h"
#include "RockMap.h"
#include "Drawer.h"

const double KICK_POWER = -10.0;
const int MAX_OUT_CAMERA_COUNT = 90;

RockEnemy::RockEnemy( const Vector& pos, DOLL doll, int hp, int force, int radius, int height, bool mass, bool head ) :
RockCharacter( pos, doll, radius, height, mass, head ),
_force( 1 ),
_hp( hp ),
_finished( false ),
_max_hp( hp ),
_start_pos( pos ),
_out_camera_count( 0 ) {
}


RockEnemy::~RockEnemy( ) {
}

void RockEnemy::reset( ) {
	setPos( _start_pos );
	_hp = _max_hp;
	_finished = false;
}

int RockEnemy::getForce( ) const {
	return _force;
}

void RockEnemy::damage( int force ) {
	if ( force < 0 ) {
		_hp = 0;
		_finished = true;
		return;
	}

	_hp -= force;
	if ( _hp < 0 ) {
		_hp = 0;
		_finished = true;
	}
}

bool RockEnemy::isFinished( ) const {
	return _finished;
}

bool RockEnemy::isDead( ) const {
	return _hp == 0;
}

ModelMV1Ptr RockEnemy::getModel( ) {
	ModelMV1Ptr model = RockDollHouse::getTask( )->getModel( getDoll( ) );
	model->setAnimTime( getAnimTime( ) );
	double rot = Vector( 0, 0, -1 ).angle( getDir( ) );
	Vector axis = Vector( 0, 1, 0 );
	if ( Vector( 0, 0, -1 ).cross( getDir( ) ).y < 0 ) {
		axis = Vector( 0, -1, 0 );
	}
	model->setRot( Matrix::makeTransformRotation( axis, rot ) );
	model->setTrans( Matrix::makeTransformTranslation( getPos( ) ) );
	return model;
}

void RockEnemy::updateInCamera( ) {
	/*bool enemy_boss = false;
	RockMilitaryPtr military = RockMilitary::getTask( );
	std::list< RockEnemyPtr > enemies = military->getEnemyList( );
	std::list< RockEnemyPtr >::iterator ite = enemies.begin( );

	if ( enemies.size( ) > 0 ) {
		enemy_boss = true;
	}
	while ( ite != enemies.end( ) ) {
		RockEnemyBossPtr boss = std::dynamic_pointer_cast< RockEnemyBoss >( *ite );
		if ( boss ) {
			enemy_boss = true;
			break;
		}ite++;
	}

	if ( Drawer::getTask( )->isInCamera( getPos( ) ) ) {
		_out_camera_count = 0;
	} else {
		_out_camera_count++;
		if ( _out_camera_count > MAX_OUT_CAMERA_COUNT && !enemy_boss ) {
			_finished = true;
		}
	}*/
	if ( Drawer::getTask( )->isInCamera( getPos( ) ) ) {
		_out_camera_count = 0;
	} else {
		_out_camera_count++;
		if ( _out_camera_count > MAX_OUT_CAMERA_COUNT ) {
			_finished = true;
		}
	}
}
