#include "PopHugDemon.h"
#include "EnemyHugDemon.h"
#include "Military.h"


PopHugDemon::PopHugDemon( const Vector& pos ) :
Pop( pos ) {
}


PopHugDemon::~PopHugDemon( ) {
}

void PopHugDemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyHugDemon( getPos( ) ) ) );
}