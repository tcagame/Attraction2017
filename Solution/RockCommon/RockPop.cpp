#include "RockPop.h"
#include "RockMilitary.h"
#include "Drawer.h"
#include "RockEnemy.h"

const int MAX_POP_COUNT = 400;

RockPop::RockPop( RockEnemyPtr enemy, bool moment ) :
_enemy( enemy ),
_pop( false ) {
	if ( moment ) {
		_count = MAX_POP_COUNT;
	} else {
		_count = 0;
	}
}


RockPop::~RockPop( ) {
}

void RockPop::update( ) {
	_count++;
	if ( _count > MAX_POP_COUNT ) {
		if ( Drawer::getTask( )->isInCamera( _enemy->getPos( ) ) ) {
			_pop = true;
			RockMilitary::getTask( )->addEnemy( _enemy );
		}
	}
}

bool RockPop::isFinished( ) const {
	return _pop;
}