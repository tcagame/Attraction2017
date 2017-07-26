#include "Military.h"
#include "Application.h"
#include "EnemyPurpleZombie.h"

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
	_enemies.push_back( EnemyPtr( new EnemyPurpleZombie( Vector( 300, 0 ) ) ) );
}


Military::~Military( ) {
}

void Military::update( ) {
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		enemy->update( );
		ite++;
	}
}

const std::list< EnemyPtr > Military::getList( ) const {
	return _enemies;
}
