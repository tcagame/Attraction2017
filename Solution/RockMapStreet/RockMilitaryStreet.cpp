#include "RockMilitaryStreet.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"
#include "RockEnemyFaceAndHand.h"
#include "RockEnemyBat.h"
#include "RockEnemyKimono.h"
#include "RockEnemyCloud.h"



RockMilitaryStreet::RockMilitaryStreet( ) {
	add( RockEnemyPtr( new RockEnemyGhost(       Vector(  500,  40, -500 ) ) ) );
	add( RockEnemyPtr( new RockEnemyRedBard(     Vector(  800,  60, -520 ) ) ) );
	add( RockEnemyPtr( new RockEnemyWaterGhost(  Vector( 1100,  60, -530 ) ) ) );
	add( RockEnemyPtr( new RockEnemyFaceAndHand( Vector( 1400, 130, -540 ) ) ) );
	add( RockEnemyPtr( new RockEnemyCloud(       Vector( 1700, 150, -550 ) ) ) );
	add( RockEnemyPtr( new RockEnemyBat(         Vector( 2000, 190, -550 ) ) ) );
	add( RockEnemyPtr( new RockEnemyKimono(      Vector( 2300, 150, -550 ) ) ) );
}


RockMilitaryStreet::~RockMilitaryStreet( ) {
}
