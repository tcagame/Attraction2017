#include "PopLady.h"
#include "EnemyLady.h"
#include "Military.h"

PopLady::PopLady( const Vector& pos ) :
Pop( pos ) {
}

PopLady::~PopLady( ) {
}

void PopLady::create( ) {
	Military::getTask( )->popUp( EnemyPtr( new EnemyLady( getPos( ) ) ) );
}