#include "PopNoFace.h"
#include "EnemyNoFace.h"
#include "Military.h"

PopNoFace::PopNoFace( const Vector& pos ) :
Pop( pos ) {
}

PopNoFace::~PopNoFace( ) {
}

void PopNoFace::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyNoFace( getPos( ) ) ) );
}