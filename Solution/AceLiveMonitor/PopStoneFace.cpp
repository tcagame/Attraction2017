#include "PopStoneFace.h"
#include "EnemyStoneFace.h"
#include "Military.h"

PopStoneFace::PopStoneFace( const Vector& pos ) :
Pop( pos ) {
}

PopStoneFace::~PopStoneFace( ) {
}

void PopStoneFace::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyStoneFace( getPos( ) ) ) );
}