#include "PopRedBird.h"
#include "EnemyRedBird.h"
#include "Military.h"

PopRedBird::PopRedBird( const Vector& pos ) :
Pop( pos ) {
}


PopRedBird::~PopRedBird( ) {
}

void PopRedBird::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyRedBird( getPos( ) ) ) );
}