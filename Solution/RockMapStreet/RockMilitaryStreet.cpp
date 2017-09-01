#include "RockMilitaryStreet.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyCloud.h"



RockMilitaryStreet::RockMilitaryStreet( ) {
	add( RockEnemyPtr( new RockEnemyGhost( Vector( 10, 40, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyRedBard( Vector( 10, 30, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyWaterGhost( Vector( -10, 30, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyFaceAndHand( Vector( -50, 50, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyCloud( Vector( -50, 50, -400 ) ) ) );
}


RockMilitaryStreet::~RockMilitaryStreet( ) {
}
