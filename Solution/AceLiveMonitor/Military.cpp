#include "Military.h"
#include "Application.h"
#include "EnemyPurpleZombie.h"
#include "EnemyFaceAndHand.h"
#include "ace_define.h"
#include "Family.h"
#include "Player.h"

PTR( Player );

MilitaryPtr Military::getTask( ) {
	return std::dynamic_pointer_cast< Military >( Application::getInstance( )->getTask( getTag( ) ) );
}


Military::Military( ) {
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
		if ( enemy->isFinished( ) ||
			 !enemy->isInScreen( ) ) {
			ite = _enemies.erase( ite );
			continue;
		}
		FamilyPtr family( Family::getTask( ) );
		for ( int i = 0; i < ACE_PLAYER_NUM; i++ ) {
			PlayerPtr player( family->getPlayer( i ) );
			if ( player->isOverlapped( enemy ) ) {
				player->damage( 1 );
			}
		}
		enemy->update( );
		ite++;
	}
}

const std::list< EnemyPtr > Military::getList( ) const {
	return _enemies;
}

void Military::popUp( EnemyPtr enemy ) {
	_enemies.push_back( enemy );
}

EnemyPtr Military::getOverLappedEnemy( CharacterConstPtr character ) const {
	EnemyPtr result = EnemyPtr( );
	std::list< EnemyPtr >::const_iterator ite = _enemies.begin( );
	while ( ite != _enemies.end( ) ) {
		EnemyPtr enemy = (*ite);
		if ( !enemy ) {
			ite++;
			continue;
		}
		if ( enemy->isOverlapped( character ) ) {
			result = enemy;
			break;
		}
		ite++;
	}
	return result;
}
