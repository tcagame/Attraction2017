#include "PopEyeDaemon.h"
#include "EnemyEyeDaemon.h"
#include "Military.h"


PopEyeDaemon::PopEyeDaemon( const Vector& pos ) :
Pop( pos ) {
}


PopEyeDaemon::~PopEyeDaemon( ) {
}

void PopEyeDaemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyEyeDaemon( getPos( ) ) ) );
}