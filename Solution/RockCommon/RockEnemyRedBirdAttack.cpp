#include "RockEnemyRedBirdAttack.h"

const int FORCE = 2;
const int HP = 99; //ã[éóìIÇ…éÄÇ»Ç»Ç¢ÇÊÇ§Ç…ÇµÇƒÇ‹Ç∑ÅB

RockEnemyRedBirdAttack::RockEnemyRedBirdAttack( const Vector pos ) :
RockEnemyAttack( pos, DOLL_NONE, _hp, FORCE, 10, 30, true, false ),
_hp( HP ) {
}


RockEnemyRedBirdAttack::~RockEnemyRedBirdAttack( ) {
}

void RockEnemyRedBirdAttack::act( ) {
	if ( isStanding( ) ) {
		_hp = 0;
	}
}

double RockEnemyRedBirdAttack::getAnimTime( ) const {
	return 0;
}
