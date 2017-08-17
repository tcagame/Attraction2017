#include "PopEyeDemon.h"
#include "EnemyEyeDemon.h"
#include "Military.h"


PopEyeDemon::PopEyeDemon( const Vector& pos ) :
Pop( pos ) {
}


PopEyeDemon::~PopEyeDemon( ) {
}

void PopEyeDemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyEyeDemon( getPos( ) ) ) );
}