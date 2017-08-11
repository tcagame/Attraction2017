#include "RockMilitaryTest.h"
#include "RockEnemyGhost.h"
#include "RockEnemyRedBard.h"
#include "RockEnemyWaterGhost.h"



RockMilitaryTest::RockMilitaryTest( ) {
	add( RockEnemyPtr( new RockEnemyGhost( Vector( 0, 40, 0 ) * 5 ) ) );
	add( RockEnemyPtr( new RockEnemyRedBard( Vector( 10, 30, 10 ) * 5 ) ) );
	add( RockEnemyPtr( new RockEnemyWaterGhost( Vector( -10, 30, 30 ) * 5 ) ) );
}


RockMilitaryTest::~RockMilitaryTest( ) {
}
