#include "PopShishimaiDaemon.h"
#include "EnemyShishimaiDaemon.h"
#include "Military.h"

PopShishimaiDaemon::PopShishimaiDaemon( const Vector& pos ) :
Pop( pos ) {
}


PopShishimaiDaemon::~PopShishimaiDaemon( ) {
}

void PopShishimaiDaemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyShishimaiDaemon( getPos( ) ) ) );
}