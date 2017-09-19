#include "RockEnemyBossRockAttack.h"

static const int MAX_HP = 1;
static const int RADIUS = 10;
static const int HEIGHT = 10;
static const double MOVE_SPEED = 0.5;
static const double JUMP_POWER = 3;

RockEnemyBossRockAttack::RockEnemyBossRockAttack( const Vector& pos, DOLL id, const Vector& dir ) :
RockEnemyAttack( pos, id, MAX_HP, 1, RADIUS, HEIGHT, true ),
_dir( dir.normalize( ) ),
_start_pos( pos ),
_jump( false ),
_back( false ) {
}

RockEnemyBossRockAttack::~RockEnemyBossRockAttack( ) {
}

void RockEnemyBossRockAttack::act( ) {
	Vector vec = getVec( ) + _dir * MOVE_SPEED;
	if ( !_back ) {
		if ( isStanding( ) ) {
			vec *= 0.6;
			if ( _jump ) {
				_back = true;
				//vec = _dir * MOVE_SPEED;
			}
			if ( !_jump ) {
				vec.y = JUMP_POWER;
				_jump = true;
			}
		}
	} else {
		vec = _dir * -MOVE_SPEED;
		vec.y -= GRAVITY;
	}
	setVec( vec );

	if ( ( getPos( ) - _start_pos ).getLength2( ) < MOVE_SPEED * MOVE_SPEED ) {
		setVec( _start_pos - getPos( ) );
		_back = false;
		_jump = false;
	}
}

double RockEnemyBossRockAttack::getAnimTime( ) const {
	return 0;
}
