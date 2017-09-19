#include "PopTurtle.h"
#include "EnemyTurtle.h"
#include "Military.h"

PopTurtle::PopTurtle( const Vector& pos ) :
Pop( pos ) {
}

PopTurtle::~PopTurtle( ) {
}

void PopTurtle::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyTurtle( getPos( ) ) ) );
}
