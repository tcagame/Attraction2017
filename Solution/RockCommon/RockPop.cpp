#include "RockPop.h"
#include "RockMilitary.h"

static const int MAX_POP_COUNT = 100;

RockPop::RockPop( RockEnemyPtr enemy ) :
_enemy( enemy ) {
}


RockPop::~RockPop( ) {
}

void RockPop::update( ) {
	_count++;
	if ( _count > MAX_POP_COUNT ) {
		RockMilitary::getTask( )->add( _enemy );
	}
}

bool RockPop::isFinished( ) const {
	return ( _count > MAX_POP_COUNT );
}