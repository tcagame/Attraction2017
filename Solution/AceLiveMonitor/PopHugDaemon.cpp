#include "PopHugDaemon.h"
#include "EnemyHugDaemon.h"
#include "Military.h"


PopHugDaemon::PopHugDaemon( const Vector& pos ) :
Pop( pos ) {
}


PopHugDaemon::~PopHugDaemon( ) {
}

void PopHugDaemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyHugDaemon( getPos( ) ) ) );
}