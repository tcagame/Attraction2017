#include "PopHand.h"
#include "EnemyHand.h"
#include "Military.h"

PopHand::PopHand( const Vector& pos ) :
Pop( pos ) {
}


PopHand::~PopHand( ) {
}

void PopHand::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyHand( getPos( ) ) ) );
}