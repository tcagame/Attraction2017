#include "RockEnemyRedBirdAttack.h"

const int FORCE = 2;
const int HP = 99; //�[���I�Ɏ��ȂȂ��悤�ɂ��Ă܂��B

RockEnemyRedBirdAttack::RockEnemyRedBirdAttack( const Vector pos ) :
RockEnemyAttack( pos, DOLL_BIRD_ATTACK, HP, FORCE, 10, 30, true, true ) {
	setDir( Vector( 0, 0, -1 ) );
}


RockEnemyRedBirdAttack::~RockEnemyRedBirdAttack( ) {
}

void RockEnemyRedBirdAttack::act( ) {
	if ( isStanding( ) ) {
		damage( -1 );
	}
}

double RockEnemyRedBirdAttack::getAnimTime( ) const {
	return 0;
}
