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
	_enemies.push_back( EnemyPtr( new EnemyPurpleZombie( Vector( 700, VIEW_STREET_Y + 60 ) ) ) );
	_enemies.push_back( EnemyPtr( new EnemyFaceAndHand( Vector( 600, VIEW_STREET_Y + 80 ) ) ) );
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
		if ( enemy->isFinished( ) ) {
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
