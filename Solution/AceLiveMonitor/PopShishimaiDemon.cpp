#include "PopShishimaiDemon.h"
#include "EnemyShishimaiDemon.h"
#include "Military.h"

PopShishimaiDemon::PopShishimaiDemon( const Vector& pos ) :
Pop( pos ) {
}


PopShishimaiDemon::~PopShishimaiDemon( ) {
}

void PopShishimaiDemon::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyShishimaiDemon( getPos( ) ) ) );
}