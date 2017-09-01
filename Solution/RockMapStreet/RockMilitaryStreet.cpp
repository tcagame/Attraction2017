#include "RockMilitaryStreet.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyBat.h"
#include "RockEnemyKimono.h"
#include "RockEnemyCloud.h"



RockMilitaryStreet::RockMilitaryStreet( ) {
	add( RockEnemyPtr( new RockEnemyGhost( Vector( 230, 40, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyRedBard( Vector( 310, 60, -500 ) ) ) );
	add( RockEnemyPtr( new RockEnemyWaterGhost( Vector( -10, 30, -400 ) ) ) );
	add( RockEnemyPtr( new RockEnemyFaceAndHand( Vector( 750, 30, -600 ) ) ) );
	add( RockEnemyPtr( new RockEnemyCloud( Vector( 690, 50, -500 ) ) ) );
	add( RockEnemyPtr( new RockEnemyBat( Vector( 400, 90, -500 ) ) ) );
	add( RockEnemyPtr( new RockEnemyKimono( Vector( -60, 50, -400 ) ) ) );
}


RockMilitaryStreet::~RockMilitaryStreet( ) {
}
