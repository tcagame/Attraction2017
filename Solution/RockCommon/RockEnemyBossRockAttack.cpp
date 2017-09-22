#include "RockEnemyBossRockAttack.h"
#include "RockFamily.h"
#include "RockPlayer.h"

static const int MAX_HP = 5;
static const int RADIUS = 10;
static const int HEIGHT = 10;
static const int ACTION_TIME = 90;
static const double MOVE_SPEED = 0.5;
static const double MAX_SPEED = 10;
static const double JUMP_POWER = 3;

RockEnemyBossRockAttack::RockEnemyBossRockAttack( const Vector& pos, DOLL id, const Vector& dir ) :
RockEnemyAttack( pos, id, MAX_HP, 2, RADIUS, HEIGHT, true ),
_dir( dir.normalize( ) ),
_start_pos( pos ) {
}

RockEnemyBossRockAttack::~RockEnemyBossRockAttack( ) {
}

void RockEnemyBossRockAttack::act( ) {
	if ( getActCount( ) % ACTION_TIME < ACTION_TIME / 2 ) {
		if ( _dir.isOrijin( ) ) {
			assaultPlayer( );
			return;
		}
		Vector vec = getVec( );
		vec.y = 0;
		vec = _dir * ( MOVE_SPEED + vec.getLength( ) );
		vec.y = getVec( ).y;
		if ( isStanding( ) ) {
			vec *= 0.6;
			vec.y = JUMP_POWER;
		}
		if ( vec.getLength( ) > MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}

		setVec( vec );
	} else {
		Vector distance = _start_pos - getPos( );
		Vector vec = getVec( );
		vec.y = 0;
		vec = distance.normalize( ) * ( MOVE_SPEED + vec.getLength( ) );
		if ( vec.getLength( ) > MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}

		if ( distance.getLength2( ) < MAX_SPEED * MAX_SPEED ) {
			vec = distance;
		}
		
		setVec( vec );
	}
}

double RockEnemyBossRockAttack::getAnimTime( ) const {
	return 0;
}


void RockEnemyBossRockAttack::assaultPlayer( ) {
	Vector distance = Vector( );
	RockFamilyPtr family = RockFamily::getTask( );
	for ( int i = 0; i < ROCK_PLAYER_NUM; i++ ) {
		RockPlayerPtr player = family->getPlayer( i );
		if ( !player->isActive( ) ||
			 player->isBubble( ) ) {
			continue;
		}
		distance = player->getPos( ) - getPos( );
	}

	if ( !distance.isOrijin( ) ) {
		Vector vec = getVec( );
		vec.y = 0;
		vec = distance.normalize( ) * ( MOVE_SPEED + vec.getLength( ) );
		if ( vec.getLength( ) > MAX_SPEED ) {
			vec = vec.normalize( ) * MAX_SPEED;
		}
		setVec( vec );
	} else {
		setVec( Vector( 0, 1, 0 ) * getVec( ).getLength( ) );
	}
}

void RockEnemyBossRockAttack::setPos(const Vector& pos) {
	RockCharacter::setPos( pos );
}

void RockEnemyBossRockAttack::damage( int force ) {
	if ( force < 0 ) {
		RockEnemy::damage( force );
	}
}
