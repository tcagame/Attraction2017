#include "PopEyeDaemon.h"
#include "EnemyEyeDaemon.h"
#include "Military.h"

const int MAX_POP_COUNT = 300;

PopEyeDaemon::PopEyeDaemon( const Vector& pos ) :
Pop( pos ),
_count( MAX_POP_COUNT ) {
}


PopEyeDaemon::~PopEyeDaemon( ) {
}

void PopEyeDaemon::update( ) {
	if ( _count > MAX_POP_COUNT ) {
		if ( isInScreen( ) ) {
			Military::getTask( )->popUp( EnemyPtr( new EnemyEyeDaemon( getPos( ) ) ) );
			_count = 0;
		}
	}
	_count++;
}